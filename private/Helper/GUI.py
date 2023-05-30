import tkinter as tk
from tkinter import filedialog
import subprocess

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

    # Run the encryption command using the subprocess module
    command = ['./vol', '-s'] + file_list + ['-o', output_file]
    subprocess.run(command)

    # Show a message box after encryption is complete
    tk.messagebox.showinfo('Encryption Complete', 'Files successfully encrypted.')

def decrypt_files():
    # Open a file dialog to select the encrypted file
    file = filedialog.askopenfilenames()

    if not file:
        return

    # Run the decryption command using the subprocess module
    command = ['./vol', '-d', file]
    subprocess.run(command)

    # Show a message box after decryption is complete
    tk.messagebox.showinfo('Decryption Complete', 'File successfully decrypted.')

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
