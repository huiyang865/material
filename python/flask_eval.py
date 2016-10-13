#!flask/bin/python
#encodig=utf-8
# _*_ coding:utf-8 _*_
# Writer : byz
# dateTime : 2016-08-05
from flask import Flask, jsonify, request, abort
import json
app = Flask(__name__)


@app.route('/ana', methods=['GET', 'POST'])
def call_analysis():
    print "Hello, World!"
    # if not request.json:
    #     abort(400)
    #
    # data = request.get_json['appIds']
    return 'data'

if __name__ == '__main__':
    # app.run(host='0.0.0.0', port=8008, use_reloader=False)
    app.run()