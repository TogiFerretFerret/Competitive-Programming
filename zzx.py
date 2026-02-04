from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import time
import os
import asyncio
from markdownify import markdownify as md

class GDriver:
    def __init__(self):
        self.driver = None
        self.user_data_dir = os.path.abspath("chrome_profile")
        if not os.path.exists(self.user_data_dir):
            os.makedirs(self.user_data_dir)

    def start_driver(self):
        if self.driver:
            try:
                # Check if alive
                self.driver.title
                return
            except:
                self.driver = None

        print("🔄 Installing/Checking ChromeDriver...")
        print("🚀 Launching Chrome...")
        options = Options()
        # Point to the standard Chromium config directory
        options.add_argument(f"user-data-dir=/home/river/.config/chromium")
        options.add_argument("profile-directory=Default")
        options.add_argument("--disable-blink-features=AutomationControlled")
        options.add_argument("--headless=new")
        options.add_experimental_option("excludeSwitches", ["enable-automation"])
        options.add_experimental_option('useAutomationExtension', False)
        service = webdriver.chrome.service.Service(executable_path="/usr/bin/chromedriver")
        self.driver = webdriver.Chrome(service=service,options=options)
        self.driver.get("https://gemini.google.com")

    def is_logged_in(self):
        try:
            current_url = self.driver.current_url
            if "accounts.google.com" in current_url or "ServiceLogin" in current_url:
                return False
            # Check for input box presence
            self.driver.find_element(By.CSS_SELECTOR, "div[role='textbox']")
            return True
        except:
            return False

    async def upload_file(self, file_path):
        if not self.driver:
            self.start_driver()
        
        if not os.path.exists(file_path):
            return False

        try:
            # Locate hidden file input. Usually it's present in the DOM.
            file_input = self.driver.find_element(By.CSS_SELECTOR, "input[type='file']")
            file_input.send_keys(os.path.abspath(file_path))
            await asyncio.sleep(2) # Wait for processing
            return True
        except Exception as e:
            print(f"Upload failed: {e}")
            return False

    async def send_message(self, message):
        if not self.driver:
            self.start_driver()

        await asyncio.sleep(2)

        if not self.is_logged_in():
            return "⚠️ **Login Required:** Browser is open on the host machine. Please log in to Google Gemini in that window, then run the command again."

        try:
            # 1. Find Input Box
            input_box = WebDriverWait(self.driver, 10).until(
                EC.presence_of_element_located((By.CSS_SELECTOR, "div[role='textbox']"))
            )
            
            # 2. Type message
            input_box.click()
            # Clear input
            input_box.send_keys(Keys.CONTROL + "a")
            input_box.send_keys(Keys.DELETE)
            await asyncio.sleep(0.2)
            
            # Send message with proper newline handling
            # Split by newlines and insert Shift+Enter between them
            lines = message.split('\n')
            for i, line in enumerate(lines):
                if line:
                    input_box.send_keys(line)
                
                # If not the last line, insert newline (Shift+Enter)
                if i < len(lines) - 1:
                    input_box.send_keys(Keys.SHIFT + Keys.ENTER)
            
            await asyncio.sleep(0.5)
            input_box.send_keys(Keys.ENTER)

            # 3. Wait for response
            print("⏳ Waiting for response...")
            await asyncio.sleep(3) 
            
            last_text = ""
            stable_count = 0
            
            # Poll for response
            for _ in range(300):  # Timeout after ~5 minutes
                print("Now polling, ", _)
                # Search for markdown container
                elements = self.driver.find_elements(By.CSS_SELECTOR, ".markdown")
                if elements:
                    latest = elements[-1]
                    html_content = latest.get_attribute("innerHTML")
                    print("Got HTML content.")
                    print(html_content)
                    
                    # Convert to Markdown
                    current_text = md(html_content, heading_style="atx").strip()
                    print("marked down")
                    
                    
                    # Check stability
                    if current_text == last_text and len(current_text) > 0 and "..." not in current_text[-3:]:
                        stable_count += 1
                        if stable_count > 2: 
                            return current_text
                    else:
                        stable_count = 0
                        last_text = current_text
                
                await asyncio.sleep(1)
            
            return last_text if last_text else "❌ Timeout or could not find response text."

        except Exception as e:
            print(f"Error in send_message: {e}")
            return f"❌ Selenium Error: {str(e)}"

    def close(self):
        if self.driver:
            self.driver.quit()
            self.driver = None

gdriver = GDriver()
if __name__ == "__main__":
    gdriver.start_driver()
    with open("op.txt","r") as f:
        op=f.read()
        f.close()
    loop = asyncio.get_event_loop()
    response = loop.run_until_complete(gdriver.send_message(op))
    with open("p.txt","r") as f:
        p=f.read()
        f.close()
    resp=loop.run_until_complete(gdriver.send_message(p))
    with open("ans.cpp","w") as f:
        f.write(resp)
        f.close()

