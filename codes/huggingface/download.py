from transformers import AutoTokenizer, AutoModelForCausalLM

model_name = "codellama/CodeLlama-7b-Instruct-hf"
directory_to_save = "CodeLlama-7b-Instruct-hf"  # This means the current directory. Modify it if needed.

# Download and save tokenizer
tokenizer = AutoTokenizer.from_pretrained(model_name)
tokenizer.save_pretrained(directory_to_save)

# Download and save model
model = AutoModelForCausalLM.from_pretrained(model_name)
model.save_pretrained(directory_to_save)
