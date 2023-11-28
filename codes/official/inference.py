import os
from llama import Llama
import torch.multiprocessing as mp
import GPUtil
import sys

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

def worker(rank, args_list, instruction, start_event, done_event, initialized_event):
    os.environ['LOCAL_RANK'] = str(args_list[rank][1])
    os.environ['RANK'] = str(rank)
    llama_instance = Llama.build(
    ckpt_dir=f"CodeLlama-{model_size}-Instruct",
    tokenizer_path=f"CodeLlama-{model_size}-Instruct/tokenizer.model",
    max_seq_len=82240,
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
                    print(f"> {result['generation']['role'].capitalize()}: {result['generation']['content']}\n",flush=True)
        done_event.set()

if __name__ == "__main__":
    mp.set_start_method('spawn')
    
    available_gpus = get_available_gpus(MP)

    os.environ['MASTER_ADDR'] = 'localhost'
    os.environ['MASTER_PORT'] = '12359'
    os.environ['WORLD_SIZE'] = str(MP)
    
    instruction_queue = mp.Queue()
    
    processes = []
    start_events = [mp.Event() for _ in range(MP)]
    done_events = [mp.Event() for _ in range(MP)]
    args_list = [(i, available_gpus[i]) for i in range(MP)]
    initialized_events = [mp.Event() for _ in range(MP)]
    
    for rank in range(MP):
        p = mp.Process(target=worker, args=(rank, args_list, instruction_queue, start_events[rank], done_events[rank], initialized_events[rank]))
        p.start()
        processes.append(p)

    # Wait for all workers to complete initialization
    for event in initialized_events:
        event.wait()
    
    while True:
        inp = input("Enter your instruction (or 'exit' to quit): ")
        
        for _ in range(MP):
            instruction_queue.put(inp)
        for start_event in start_events:
            start_event.set()

        if inp == 'exit':
            for p in processes:
                p.join()
            break
        else:
            for done_event in done_events:
                done_event.wait()
                done_event.clear()
