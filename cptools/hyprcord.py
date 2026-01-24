import subprocess
def get_zenity_input(prompt_text="Enter your message:"):
    """
    Opens a Zenity text entry dialog and returns the text entered by the user.
    Returns None if the user cancels or closes the window.
    """
    try:
        # We use subprocess.run for a cleaner implementation than Popen for simple commands
        result = subprocess.run(
            ['zenity', '--entry', '--text', "", "--title", ""],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True  # Ensures stdout is returned as a string, not bytes
        )

        # returncode 0 means the user clicked 'OK'. 
        # returncode 1 usually means 'Cancel' or closed window.
        if result.returncode == 0:
            return result.stdout.strip()
        return None

    except FileNotFoundError:
        print("Error: 'zenity' is not installed or not found in PATH.")
        return None
def send_msg(msg: str):
    process = subprocess.Popen(['picord'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    _, _ = process.communicate(input=msg.encode())
    process.wait()
inp=get_zenity_input()
if inp:
    send_msg(inp)

