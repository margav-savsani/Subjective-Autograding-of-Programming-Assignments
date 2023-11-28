from transformers import AutoModelForCausalLM, AutoTokenizer
import csv
import pandas as pd

MAX_LENGTH = 1000
MODEL_SIZE = "7b"
MAX_ROWS = 1000000  # Adjust the maximum number of rows to process as needed

MODEL_DIRECTORY_MAP = {
    "34b": "CodeLlama-34b-Instruct-hf",
    "7b": "CodeLlama-7b-Instruct-hf",
    "13b": "CodeLlama-13b-Instruct-hf"
}
DEFAULT_SYSTEM_PROMPT = "You are a helpful, respectful and honest assistant. Always answer as helpfully as possible, while being safe.  Your answers should not include any harmful, unethical, racist, sexist, toxic, dangerous, or illegal content. Please ensure that your responses are socially unbiased and positive in nature.\\n\\nIf a question does not make any sense, or is not factually coherent, explain why instead of answering something not correct. If you don't know the answer to a question, please don't share false information."
# DEFAULT_SYSTEM_PROMPT = "Always answer as helpfully as possible."

def initialize_model_and_tokenizer():
    model_directory_path = MODEL_DIRECTORY_MAP[MODEL_SIZE]
    tokenizer = AutoTokenizer.from_pretrained(model_directory_path)
    tokenizer.pad_token = tokenizer.eos_token
    model = AutoModelForCausalLM.from_pretrained(model_directory_path, device_map="auto").eval()
    return tokenizer, model

def format_prompt(history):
    formatted_prompt = ""
    new_start = True
    for message in history:
        if new_start:
            formatted_prompt += "<s>[INST] "
            new_start = False
        if message['role'] == 'system':
            formatted_prompt += f"<<SYS>>\\n{message['content']}\\n<</SYS>>\\n\\n"
        elif  message['role'] == 'user':
            formatted_prompt += f"{message['content']}"
            formatted_prompt += " [/INST]"
        elif message['role'] == 'assistant':
            formatted_prompt += f" {message['content']}"
            formatted_prompt += " </s>"
            new_start = True    
    return formatted_prompt

def generate_response(prompt, history, tokenizer, model, max_length=MAX_LENGTH, add_system_prompt=False):
    if add_system_prompt:
        history.extend([{'role': 'system', 'content': DEFAULT_SYSTEM_PROMPT}])
    history.extend([{'role': 'user', 'content': prompt}])
    formatted_prompt = format_prompt(history)
    
    inputs = tokenizer(formatted_prompt, return_tensors="pt", truncation=True, max_length=max_length).to("cuda")
    output = model.generate(
        inputs["input_ids"],
        attention_mask=inputs["attention_mask"],
        pad_token_id=tokenizer.eos_token_id,
        do_sample=True,
        top_p=0.95,
        temperature=0.2,
        max_new_tokens=max_length
    )
    new_tokens = output[0][inputs["input_ids"].shape[1]:]
    response = tokenizer.decode(new_tokens, skip_special_tokens=True)

    return response

if __name__ == "__main__":
    tokenizer, model = initialize_model_and_tokenizer()
    print("Model and tokenizer initialized. Waiting for prompts...")

    history = []
    add_system_prompt = True

    # Load the CSV file
    csv_file = 'grading_without_example.csv'  # Update with your CSV file path
    column_name = 'inference_prompt'  # Replace with the name of the column you want to use

    # Define the output CSV file path
    output_csv_file = 'output_'+csv_file

    with open(csv_file, 'r') as file:
        csv_reader = csv.DictReader(file)
        rows_to_process = list(csv_reader)[:MAX_ROWS]  # Get a limited number of rows

    for row in rows_to_process:
        prompt = row[column_name]

        response = generate_response(prompt, history, tokenizer, model, max_length=MAX_LENGTH, add_system_prompt=add_system_prompt)
        add_system_prompt = False

        row['generated_response'] = response  # Add the generated response to the row
        add_system_prompt=False
        history.extend([
            {'role': 'assistant', 'content': response}
        ])
        # history.clear()
        # add_system_prompt = True


    # Save the modified CSV with the generated responses
    df = pd.DataFrame(rows_to_process)
    df.to_csv(output_csv_file, index=False)
    print(f"Responses added to '{output_csv_file}'.")
