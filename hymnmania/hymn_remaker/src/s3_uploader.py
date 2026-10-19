import os
import boto3
import logging
from botocore.exceptions import NoCredentialsError, ClientError

logger = logging.getLogger(__name__)

class S3Uploader:
    def __init__(self, access_key=None, secret_key=None, region_name=None, endpoint_url=None):
        """
        Initialize the S3 Uploader.

        Args:
            access_key (str): AWS Access Key ID. Defaults to AWS_ACCESS_KEY_ID env var.
            secret_key (str): AWS Secret Access Key. Defaults to AWS_SECRET_ACCESS_KEY env var.
            region_name (str): AWS Region Name. Defaults to AWS_DEFAULT_REGION env var.
            endpoint_url (str): Custom endpoint URL (for MinIO, R2, etc). Defaults to AWS_ENDPOINT_URL.
        """
        self.access_key = access_key or os.environ.get("AWS_ACCESS_KEY_ID")
        self.secret_key = secret_key or os.environ.get("AWS_SECRET_ACCESS_KEY")
        self.region_name = region_name or os.environ.get("AWS_DEFAULT_REGION")
        self.endpoint_url = endpoint_url or os.environ.get("AWS_ENDPOINT_URL")

        if not self.access_key or not self.secret_key:
            logger.warning("AWS Credentials not fully configured. S3 Uploader may fail unless using IAM roles.")

        try:
            # Initialize S3 client. Boto3 automatically falls back to env vars and IAM roles if explicit args are None.
            self.s3_client = boto3.client(
                's3',
                aws_access_key_id=self.access_key,
                aws_secret_access_key=self.secret_key,
                region_name=self.region_name,
                endpoint_url=self.endpoint_url
            )
        except Exception as e:
            logger.error(f"Failed to initialize S3 client: {e}")
            self.s3_client = None

    def upload_file(self, file_path, bucket_name, object_name=None, acl='public-read'):
        """
        Upload a file to an S3 bucket.

        Args:
            file_path (str): File to upload.
            bucket_name (str): Bucket to upload to.
            object_name (str): S3 object name. If not specified then file_path's basename is used.
            acl (str): Access Control List. Defaults to 'public-read' so users can view generated links.

        Returns:
            str: Public URL of the uploaded file if successful, else None.
        """
        if not self.s3_client:
            logger.error("S3 client not initialized. Cannot upload.")
            return None

        if not os.path.exists(file_path):
            logger.error(f"File not found: {file_path}")
            return None

        # If S3 object_name was not specified, use file_name
        if object_name is None:
            object_name = os.path.basename(file_path)

        try:
            logger.info(f"Uploading {file_path} to s3://{bucket_name}/{object_name}...")

            # Determine content type based on extension
            content_type = 'application/octet-stream'
            if file_path.endswith('.mp4'):
                content_type = 'video/mp4'
            elif file_path.endswith('.wav'):
                content_type = 'audio/wav'
            elif file_path.endswith('.json'):
                content_type = 'application/json'

            self.s3_client.upload_file(
                file_path,
                bucket_name,
                object_name,
                ExtraArgs={'ACL': acl, 'ContentType': content_type}
            )

            # Construct the public URL
            if self.endpoint_url:
                # Custom endpoint (like MinIO)
                url = f"{self.endpoint_url}/{bucket_name}/{object_name}"
            else:
                # Standard AWS S3
                region = self.region_name or 'us-east-1'
                if region == 'us-east-1':
                    url = f"https://s3.amazonaws.com/{bucket_name}/{object_name}"
                else:
                    url = f"https://s3-{region}.amazonaws.com/{bucket_name}/{object_name}"

            logger.info(f"Upload successful. URL: {url}")
            return url

        except FileNotFoundError:
            logger.error(f"The file was not found: {file_path}")
            return None
        except NoCredentialsError:
            logger.error("AWS credentials not available.")
            return None
        except ClientError as e:
            logger.error(f"S3 ClientError during upload: {e}")
            return None
        except Exception as e:
            logger.error(f"Unexpected error uploading to S3: {e}")
            return None

if __name__ == "__main__":
    import sys
    if len(sys.argv) > 2:
        uploader = S3Uploader()
        url = uploader.upload_file(sys.argv[1], sys.argv[2])
        print(f"Uploaded to: {url}")
    else:
        print("Usage: python s3_uploader.py <file_path> <bucket_name>")
