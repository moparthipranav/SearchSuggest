from flask import Flask, render_template, request, jsonify
import subprocess
import os

app = Flask(__name__)

# Path to your compiled C++ executable
CPP_EXE = os.path.join(os.path.dirname(__file__), "query_engine.exe")

@app.route('/')
def index():
    """Renders the main search interface."""
    return render_template('index.html')

@app.route('/search')
def search():
    """
    Handles autocomplete requests.
    
    1. Receives a query string 'q' from the frontend.
    2. Executes the C++ query engine via subprocess.
    3. Parses the output and returns a JSON response.
    """
    query = request.args.get('q', '')
    if len(query) < 2:
        return jsonify([])

    # Run the C++ executable and pass the query via stdin
    process = subprocess.Popen([CPP_EXE], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    stdout, stderr = process.communicate(input=query)

    # Parse the output based on the "|" separator we added in C++
    results = []
    parts = stdout.strip().split('|')
    for part in parts:
        if part.strip():
            results.append(part.strip().split(' '))
            
    return jsonify(results)

if __name__ == '__main__':
    app.run(debug=True)