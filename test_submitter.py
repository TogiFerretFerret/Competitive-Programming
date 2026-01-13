import sys
file=sys.argv[1]
import json
import requests
# check file (program) is cpp
if not file.endswith('.cpp'):
    print("Error: Only .cpp files are supported in this test.")
    sys.exit(1)
with open(file, 'r') as f:
    code = f.read()
# get first 3 lines
lines = code.split('\n')
if len(lines) < 3:
    print("Error: Code file must have at least 3 lines.")
    sys.exit(1)
problem_id = lines[0].strip()
judge=lines[1].strip()
if judge.split(": ")[1].strip()!="Codeforces":
    print("Error: Only Codeforces judge is supported in this test.")
    sys.exit(1)
url = lines[2].strip()
url=url.split(": ")[1].strip()
# extract problem id from url
if "codeforces.com/problemset/problem/" not in url:
    print("Error: Invalid Codeforces problem URL.")
    sys.exit(1)
parts = url.split("https://codeforces.com/problemset/problem/")[1]
merged=parts.replace("/", "")
print("Extracted Problem ID:", merged)
# submit code to local server
submit_url='http://localhost:5000/'
# two endpoints, /submit and /status
submit_endpoint = submit_url + 'submit'
status_endpoint = submit_url + 'status'
# POST to submit endpoint, json problem_id and code
code='\n'.join(lines)
pkg={'problem_id': merged, 'code': code}
do_submit = input("Do you want to submit the code? (y/n): ")
ds=None
if do_submit.lower() != 'y':
    ds=False
else:
    ds=True
if ds:
    try:
        response = requests.post(submit_endpoint, json=pkg, verify=False)
        if response.status_code == 200:
            print("Submission Response:", response.json())
        else:
            print("Error in submission:", response.text)
    except Exception as e:
        print("Exception during submission:", str(e))
        sys.exit(1)
input("Press Enter to check status...")
# GET to status endpoint
if not ds:
    # get submission id from user
    sub_id = input("Enter the submission ID to check status: ")
import time
while True:
    try:
        if ds:
            response = requests.get(status_endpoint, verify=False)
        else:
            response = requests.get(status_endpoint, params={'submission_id': sub_id}, verify=False)
        if response.status_code == 200:
            print("Status Response:", response.json())
        else:
            print("Error in status check:", response.text)
    except Exception as e:
        print("Exception during status check:", str(e))
        sys.exit(1)
    input("Check again? Press Enter to continue or type 'exit' to quit: ")
    ans = input()
    if ans.lower() == 'exit':
        break
