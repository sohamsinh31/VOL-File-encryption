import tkinter as tk
from tkinter import filedialog, messagebox
import subprocess
import os

def encrypt_files():
    # Open a file dialog to select files
    files = filedialog.askopenfilenames()

    if not files:
        return

    # Open a file dialog to select the output directory and filename
    output_file = filedialog.asksaveasfilename(defaultextension='.vol')

    if not output_file:
        return

    # Convert the files to a list of strings
    file_list = [str(file) for file in files]

    # Convert the list to a single string
    vol_executable = os.path.join(os.getcwd(), 'vol')  # Get the absolute path to 'vol' in the current directory
    command = [vol_executable, '-s'] + file_list + ['-o', output_file]
    command_string = ' '.join(command)

    # Run the encryption command using the subprocess module
    try:
        subprocess.run(command_string, shell=True, check=True)
        # Show a message box after encryption is complete
        messagebox.showinfo('Encryption Complete', 'Files successfully encrypted.')
    except subprocess.CalledProcessError:
        # An error occurred during encryption
        messagebox.showerror('Encryption Error', 'An error occurred during encryption.')

def decrypt_files():
    # Open a file dialog to select the encrypted file
    selected_file = filedialog.askopenfilename()

    if not selected_file:
        return

    # Check if the selected file exists
    if not os.path.exists(selected_file):
        messagebox.showerror('File Not Found', 'The selected file does not exist.')
        return

    # Convert the list to a single string
    vol_executable = os.path.join(os.getcwd(), 'vol')  # Get the absolute path to 'vol' in the current directory
    command = [vol_executable, '-d', selected_file]
    command_string = ' '.join(command)

    # Run the decryption command using the subprocess module
    try:
        subprocess.run(command_string, shell=True, check=True)
        # Show a message box after decryption is complete
        messagebox.showinfo('Decryption Complete', 'File successfully decrypted.')
    except subprocess.CalledProcessError:
        # An error occurred during decryption
        messagebox.showerror('Decryption Error', 'An error occurred during decryption.')

def main():
    # Create the main window
    window = tk.Tk()

    # Create a button to select files and encrypt
    encrypt_button = tk.Button(window, text='Select Files and Encrypt', command=encrypt_files)
    encrypt_button.pack()

    # Create a button to select an encrypted file and decrypt
    decrypt_button = tk.Button(window, text='Select Encrypted File and Decrypt', command=decrypt_files)
    decrypt_button.pack()

    # Start the main loop
    window.mainloop()

print(os.getcwd())
main()
