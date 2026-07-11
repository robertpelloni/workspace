import pika
import json
import redis
import time
import os
import sys

RABBITMQ_HOST = os.environ.get('RABBITMQ_HOST', 'localhost')
REDIS_HOST = os.environ.get('REDIS_HOST', 'localhost')

# Connect to Redis
r = redis.Redis(host=REDIS_HOST, port=6379, db=0)

def render_job(ch, method, properties, body):
    job_data = json.loads(body)
    job_id = job_data.get('job_id')

    print(f" [x] Received job {job_id}")

    # Update status to processing
    if job_id:
        r.set(f"job:{job_id}:status", "processing")

    # Simulate heavy ML work
    time.sleep(5)

    # Update status to completed
    if job_id:
        r.set(f"job:{job_id}:status", "completed")

    print(f" [x] Finished job {job_id}")
    ch.basic_ack(delivery_tag=method.delivery_tag)

def main():
    connection = pika.BlockingConnection(pika.ConnectionParameters(host=RABBITMQ_HOST))
    channel = connection.channel()

    channel.queue_declare(queue='render_jobs', durable=True)
    channel.basic_qos(prefetch_count=1)
    channel.basic_consume(queue='render_jobs', on_message_callback=render_job)

    print(' [*] Waiting for jobs. To exit press CTRL+C')
    channel.start_consuming()

if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print('Interrupted')
        try:
            sys.exit(0)
        except SystemExit:
            os._exit(0)
