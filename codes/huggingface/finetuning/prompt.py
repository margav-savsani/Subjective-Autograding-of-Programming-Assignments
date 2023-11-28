import os
import pandas as pd
from fuzzywuzzy import fuzz
 
def create_grading_dict(grading_excel_file, grading_sheet_name, grading_id_column_index, grading_grade_column_index):
    # Create a dictionary to store student IDs and grades
    grading_dict = {}

    # Read the grading Excel file
    grading_data = pd.read_excel(grading_excel_file, sheet_name=grading_sheet_name, header=None)

    # Iterate through rows in the grading data
    for index, row in grading_data.iterrows():
        student_id = row[grading_id_column_index]
        grade = row[grading_grade_column_index]
        grading_dict[str(student_id)] = grade

    return grading_dict

def create_prompts_dataframe(grading_excel_file, grading_sheet_name, grading_id_column_index, grading_grade_column_index):
   

    # Create a dictionary of student IDs and grades
    grading_dict = create_grading_dict(grading_excel_file, grading_sheet_name, grading_id_column_index, grading_grade_column_index)

    # Create a list to store the prompts and missing files information
    prompts = []

    # Iterate through student submissions
    for lab_folder in os.listdir(os.path.join(student_submissions_dir, lab)):
        lab_folder_path = os.path.join(student_submissions_dir, lab, lab_folder)
        if os.path.isdir(lab_folder_path):
            student_id = lab_folder
            # Check if the student ID exists in the grading dictionary
            if student_id in grading_dict:
                true_grade = grading_dict[str(student_id)]
            else:
                true_grade = 'Not Found'

            ideal_output = f'[SCORE]\n{true_grade}\n[\SCORE]'
            # Create the prompt for the instructor
            instructor_prompt = "[INSTRUCTOR]\n[Files]"
            missing_instructor_files = []

            for file_name in instructor_files_to_include:
                matching_files = [f for f in os.listdir(os.path.join(instructor_resources_dir, lab)) if fuzz.ratio(f, file_name) >= 80]
                if matching_files:
                    matched_file_name = matching_files[0]  # Use the first matching file
                    file_path = os.path.join(instructor_resources_dir, lab, matched_file_name)
                    with open(file_path, 'r') as file:
                        file_content = file.read()
                        instructor_prompt += f"\n[FILENAME]\n{matched_file_name}\n[/FILENAME]\n[CONTENT]\n{file_content}\n[/CONTENT]"
                else:
                    missing_instructor_files.append(file_name)

            instructor_prompt += "\n[/Files]\n[/INSTRUCTOR]"

            # Create the rubric
            rubric = f"\n\n[RUBRIC]\nIs the Code well structured and commented\n[POSSIBLESCORES]\n[0,1,2]\n[/POSSIBLESCORES]\n[/RUBRIC]"

            # Create the prompt for the student
            student_prompt = f"\n\n[STUDENT]\n[FILES]"
            missing_student_files = []

            for file_name in student_files_to_include:
                matching_files = [f for f in os.listdir(lab_folder_path) if fuzz.ratio(f, file_name) >= 80]
                if matching_files:
                    matched_file_name = matching_files[0]  # Use the first matching file
                    file_path = os.path.join(lab_folder_path, matched_file_name)
                    with open(file_path, 'r') as file:
                        file_content = file.read()
                        student_prompt += f"\n[FILENAME]\n{matched_file_name}\n[/FILENAME]\n[CONTENT]\n{file_content}\n[/CONTENT]"
                else:
                    missing_student_files.append(file_name)

            student_prompt += "\n[/FILES]\n[/STUDENT]"

            # Combine the prompts and store them along with missing files, student ID, and true grade
            combined_prompt = instructor_prompt + rubric + student_prompt
            prompts.append({
                'student_id': student_id,
                'user_prompt': combined_prompt,
                'missing_instructor_files': ', '.join(missing_instructor_files),
                'missing_student_files': ', '.join(missing_student_files),
                'true_grade': true_grade,
                'ideal_output':ideal_output
            })

    # Create a pandas DataFrame from the prompts list
    prompts_df = pd.DataFrame(prompts)
    
    return prompts_df

def filter_dataframe(dataframe):
    # Define the grade criteria
    grade_criteria = [0, 1, 2]

    # Filter the DataFrame to remove rows where the missing files of instructor or student are not empty
    filtered_dataframe = dataframe[
        (dataframe['missing_instructor_files'] == '') &
        (dataframe['missing_student_files'] == '') &
        (dataframe['true_grade'].astype(float).isin(grade_criteria))  # Check if the grade is in the criteria
    ].copy()
    filtered_dataframe.drop(columns=['missing_instructor_files','missing_student_files','true_grade'],inplace=True)
    return filtered_dataframe
    
if __name__ == "__main__":

    # Set the paths for instructor resources and student submissions
    instructor_resources_dir = '../cs293_dataset/instructor_resources_provided'
    student_submissions_dir = '../cs293_dataset/student_submissions'
    lab = 'Lab 1'

    # Define the list of instructor files and student files you want to include
    instructor_files_to_include = ['moodle_description.txt']
    student_files_to_include = ['linearQueue.cpp', 'circularQueue.cpp']

    grading_excel_file = '../cs293_dataset/grades.xlsx'
    grading_sheet_name = 'Lab1'
    grading_id_column_index = 0  # Index for the first column (ID)
    grading_grade_column_index = 6  # Index for the seventh column (Grade)

    # Create prompts DataFrame
    prompts_df = create_prompts_dataframe(grading_excel_file, grading_sheet_name, grading_id_column_index, grading_grade_column_index)
    # Filter the DataFrame 
    filtered_df = filter_dataframe(prompts_df)
    # Save the filtered data to a CSV file
    filtered_df.to_csv('prompts.csv', index=False)
    print(f'Prompts have been generated and saved')
