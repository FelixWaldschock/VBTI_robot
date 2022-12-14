from flask import Flask
from turbo_flask import Turbo

turbo = Turbo()


def create_app():
    app = Flask(__name__)
    turbo.init_app(app)

    return app


def index():
    return '''
        <html>
            <head>
            {{ turbo() }}
                <style>
                    label, input {
                        display: block;
                    }

                    div {
                        margin: 0 auto;
                        width: 200px;
                    }
                </style>
            </head>
            <body>
                <form method="POST">
                    <div>
                        <label>x: <input type="number" name="x" /></label>
                        <label>z: <input type="number" name="z" /></label>
                        <input type="submit" value="submit" />
                    </div>
                </form>
            </body>
        </html>
    '''
