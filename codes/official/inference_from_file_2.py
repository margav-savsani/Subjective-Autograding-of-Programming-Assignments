import os
import torch.multiprocessing as mp
import GPUtil
import sys
import csv

from llama import Llama

MODEL_SIZE_MAP = {
    "7b": 1,
    "13b": 2,
    "34b": 4
}

model_size = "7b"
MP = MODEL_SIZE_MAP[model_size]

def get_available_gpus(num_gpus):
    devices = GPUtil.getAvailable(order='memory', limit=num_gpus)
    if len(devices) < num_gpus:
        raise RuntimeError(f"Less than {num_gpus} GPUs with free memory available.")
    return devices

def worker(rank, args_list, instruction, start_event, done_event, initialized_event, response_queue):
    os.environ['LOCAL_RANK'] = str(args_list[rank][1])
    os.environ['RANK'] = str(rank)
    llama_instance = Llama.build(
    ckpt_dir=f"CodeLlama-{model_size}-Instruct",
    tokenizer_path=f"CodeLlama-{model_size}-Instruct/tokenizer.model",
    max_seq_len=40048,
    max_batch_size=1,
    
    )      
   
    initialized_event.set()  # Signal that the worker is ready
    while True:
        start_event.wait()
        # Once the event is seen, immediately clear it
        start_event.clear()
        current_instruction = instruction.get()
        if current_instruction == "exit":
            break
        results = llama_instance.chat_completion(
            [[{"role": "user", "content": current_instruction}]],
            max_gen_len=None,
            temperature=0.2,
            top_p=0.95,
        )
        sys.stdout = sys.__stdout__
        if rank == 0:
            for result in results:
                response_queue.put(result['generation']['content'])
        done_event.set()

if __name__ == "__main__":
    input_filepath = 'test_lab1.csv'
    output_filepath = 'output_test_2.csv'
    mp.set_start_method('spawn')

    available_gpus = get_available_gpus(MP)

    os.environ['MASTER_ADDR'] = 'localhost'
    os.environ['MASTER_PORT'] = '12351'
    os.environ['WORLD_SIZE'] = str(MP)
    
    instruction_queue = mp.Queue()
    response_queue = mp.Queue()

    processes = []
    start_events = [mp.Event() for _ in range(MP)]
    done_events = [mp.Event() for _ in range(MP)]
    args_list = [(i, available_gpus[i]) for i in range(MP)]
    initialized_events = [mp.Event() for _ in range(MP)]
    

    for rank in range(MP):
        p = mp.Process(target=worker, args=(rank, args_list, instruction_queue, start_events[rank], done_events[rank], initialized_events[rank], response_queue))
        p.start()
        processes.append(p)

    for event in initialized_events:
        event.wait()

    # CSV I/O
    with open(input_filepath, "r", newline="") as inp_file, open(output_filepath, "w", newline="") as out_file:
            reader = csv.DictReader(inp_file)  # Using DictReader to read CSV by column names
            fieldnames = reader.fieldnames  # Grab the fieldnames (column headers)
            
            # Assuming fieldnames is not None
            if "Prompt" not in fieldnames:
                raise ValueError("Input CSV does not have a 'Prompt' column.")
            
            # Adding new column for generated responses
            fieldnames.append("generated_response")
            
            writer = csv.DictWriter(out_file, fieldnames=fieldnames)  # Using DictWriter to write CSV by column names
            writer.writeheader()  # Writing the column headers to the output CSV

            for row in reader:
                prompt = row["Prompt"]

                for _ in range(MP):
                    instruction_queue.put(prompt)
                for start_event in start_events:
                    start_event.set()

                for done_event in done_events:
                    done_event.wait()
                    done_event.clear()

                response = response_queue.get()
                row["generated_response"] = response  # Adding generated response to the row
                writer.writerow(row)  # Writing the entire row (with all columns) to the output CSV

    # Cleanup
    for _ in range(MP):
        instruction_queue.put('exit')
    for start_event in start_events:
        start_event.set()
    for p in processes:
        p.join()
