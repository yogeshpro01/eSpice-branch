from flask import Flask, request
import compiler


app = Flask(__name__)

@app.route('/translate', methods=['POST'])
def index():
    try:
        code = compiler.compile(request.form['program'], join=True)
        return code
    except compiler.BrainfuckCompilerError:
        return '', 400


if __name__ == '__main__':
    app.run(port=3000)
