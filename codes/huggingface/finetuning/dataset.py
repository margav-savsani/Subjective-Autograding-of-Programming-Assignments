import json
import pandas as pd

def convert_csv_to_json(df):
    def is_valid_json(json_path):
        try:
            with open(json_path, 'r') as json_file:
                json.load(json_file)
            return True
        except json.JSONDecodeError:
            return False
    # Initialize an empty dictionary to hold the dataset
    dataset = {}
    # Iterate through unique values in the dataset type column
    for dataset_type in df[dataset_type_column].unique():
        # Filter the DataFrame based on the dataset type
        filtered_df = df[df[dataset_type_column] == dataset_type]
        # Create a dataset split with all columns from the DataFrame except 'dataset_type'
        dataset[dataset_type] = {
            key: filtered_df[key].tolist() for key in df.columns if key != dataset_type_column
        }
    # Save the dataset as a JSON file
    with open(json_path, 'w') as json_file:
        json.dump(dataset, json_file)

    if is_valid_json(json_path):
        print("The JSON file is correctly formatted.")
    else:
        print("The JSON file is not correctly formatted.")
        
def create_inference_and_finetuning_prompts(df):
    # Create new columns 'inference_prompt' and 'finetuning_prompt'
    df['inference_prompt'] = df.apply(lambda row: f'<s>[INST] <<SYS>>\n{system_prompt}\n<</SYS>>\n\n{row[user_prompt_column]} [/INST]', axis=1)
    df['finetuning_prompt'] = df.apply(lambda row: f'<s>[INST] <<SYS>>\n{system_prompt}\n<</SYS>>\n\n{row[user_prompt_column]} [/INST] {row[model_output_column]}', axis=1)
    return df

if __name__ == "__main__":
    # Load the CSV file
    user_prompt_column = 'user_prompt'
    model_output_column = 'ideal_output'
    initial_path = "prompts.csv"
    csv_path = "dataset.csv"
    json_path = "dataset.json"
    dataset_type_column = "dataset_type"
    split_value = 0.8
    max_rows = 10  # Maximum number of rows to keep
    
    # system_prompt = "You are a helpful, respectful and honest assistant. Always answer as helpfully as possible, while being safe. Your answers should not include any harmful, unethical, racist, sexist, toxic, dangerous, or illegal content. Please ensure that your responses are socially unbiased and positive in nature.\\n\\nIf a question does not make any sense, or is not factually coherent, explain why instead of answering something not correct. If you don't know the answer to a question, please don't share false information. You have the task of grading a programming assignment submission. The problem statement and resources provided by the instructor will be given between [INSTRUCTOR] and [/INSTRUCTOR] tags. The rubric that is supposed to be graded will be given between [RUBRIC] and [/RUBRIC] tags. The student submission will be between [STUDENT] and [/STUDENT] tags. You are supposed to come up with a score for the submission for the given rubric. Do not give verbose output and give consise output in the exact format [SCORE]\n(Score that you give)\n[/SCORE]"
    system_prompt = "You have the task of grading a programming assignment submission. The problem statement and resources provided by the instructor will be given between [INSTRUCTOR] and [/INSTRUCTOR] tags. The rubric that is supposed to be graded will be given between [RUBRIC] and [/RUBRIC] tags. The student submission will be between [STUDENT] and [/STUDENT] tags. You are supposed to come up with a score for the submission for the given rubric. Do not give verbose output and give consise output in the exact format [SCORE]\n(Score that you give)\n[/SCORE]"
    df = pd.read_csv(initial_path)
    # Limit the DataFrame to the maximum number of rows
    if max_rows is not None and len(df) > max_rows:
        df = df[:max_rows]
    # Create the 'split' column based on the specified 'split_value'
    df['split'] = df.index / len(df)  # Assuming the index represents the percentage of the dataset
    # Create the 'dataset_type' column based on the 'split_value'
    df['dataset_type'] = df['split'].apply(lambda x: 'train' if x < split_value else 'test')
    # Create the 'inference_prompt' and 'finetuning_prompt' columns
    df = create_inference_and_finetuning_prompts(df)
    df=df[['dataset_type','inference_prompt','finetuning_prompt','ideal_output']]
    # Save the updated DataFrame to a CSV file
    df.to_csv(csv_path, index=False)

    # Convert the CSV to JSON
    convert_csv_to_json(df)

    print(f"Conversion complete. JSON file saved as {json_path}")
