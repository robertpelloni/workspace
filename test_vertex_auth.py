import os
import google.auth
from google.auth.transport.requests import Request

os.environ['GOOGLE_APPLICATION_CREDENTIALS'] = r'C:\Users\hyper\workspace\adc.json'

try:
    credentials, project = google.auth.default()
    credentials.refresh(Request())
    print(f"Successfully authenticated with project: {project}")
    print(f"Token: {credentials.token[:10]}...")
except Exception as e:
    print(f"Authentication failed: {e}")
