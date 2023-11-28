import torch
import transformers
from peft import LoraConfig
from transformers import AutoModelForCausalLM, BitsAndBytesConfig, AutoTokenizer
from trl import SFTTrainer
from datasets import load_dataset  # Add this import

# Define your dataset JSON file path
DATASET_JSON_PATH = "my_custom_dataset.json"  # Replace with your JSON file path

MODEL_DIRECTORY_MAP = {
    "34b": "CodeLlama-34b-Instruct-hf",
    "7b": "CodeLlama-7b-Instruct-hf",
    "13b": "CodeLlama-13b-Instruct-hf"
}

MAX_LENGTH = 1600
MODEL_SIZE = "7b"  # Change this value to '34b', '7b', or '13b' as needed

qlora_config = LoraConfig(
    r=16,
    lora_alpha=32,
    lora_dropout=0.05,
    bias="none",
    task_type="CAUSAL_LM"
)

bnb_config = BitsAndBytesConfig(
    load_in_4bit=True,
    bnb_4bit_use_double_quant=True,
    bnb_4bit_quant_type="nf4",
    bnb_4bit_compute_dtype=torch.bfloat16
)

def initialize_model_and_tokenizer():
    model_directory_path = MODEL_DIRECTORY_MAP[MODEL_SIZE]
    tokenizer = AutoTokenizer.from_pretrained(model_directory_path)
    tokenizer.pad_token = tokenizer.eos_token
    model = AutoModelForCausalLM.from_pretrained(model_directory_path, device_map="auto",quantization_config=bnb_config).eval()
    return tokenizer, model

if __name__ == "__main__":
    tokenizer, model = initialize_model_and_tokenizer()
    print("Model and tokenizer initialized.")

    # Load the dataset from the JSON file
    dataset = load_dataset(DATASET_JSON_PATH)

    # Extract the train and test splits from the loaded dataset
    train_dataset = dataset['train']
    test_dataset = dataset['test']

    supervised_finetuning_trainer = SFTTrainer(
        model,
        train_dataset=train_dataset,
        eval_dataset=test_dataset,
        args=transformers.TrainingArguments(
            per_device_train_batch_size=1,
            gradient_accumulation_steps=4,
            learning_rate=2e-4,
            max_steps=5000,
            output_dir=f"./{MODEL_SIZE}_finetuned",
            optim="paged_adamw_8bit",
            fp16=True,
        ),
        tokenizer=tokenizer,
        peft_config=qlora_config,
        dataset_text_field="text",  # Assuming "text" is the field name in your dataset
        max_seq_length=MAX_LENGTH
    )

    supervised_finetuning_trainer.train()
