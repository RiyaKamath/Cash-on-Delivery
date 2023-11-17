from flask import Flask, send_from_directory
from threading import Semaphore

app = Flask(_name_, static_url_path='', static_folder='.')
semaphore = Semaphore(1)  # Only one thread can access the resource at a time

@app.route('/')
def index():
    return send_from_directory('.', 'index.html')

@app.route('/pay', methods=['POST'])
def pay():
    semaphore.acquire()
    try:
        pass
        return 'Payment processed', 200
    finally:
        semaphore.release()

if _name_ == '_main_':
    app.run(port=5000)
