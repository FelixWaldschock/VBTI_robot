from pywebio import start_server, config
from pywebio.input import *
from pywebio.output import *


"""@config(theme='dark')
def main():
    put_grid([
        [span(put_markdown('## Section A'), col=3)],
        [put_markdown('### Chart 1'), put_markdown(
            '### Chart 2'), put_markdown('### Chart 3')],
        [put_markdown(md), put_scope('1-2'), put_scope('1-3')],
        [span(put_markdown('## Section B'), col=2, row=1),
         put_markdown('## Section C')],
        [span(put_row([
            put_select('x', help_text='X column', options=['a', 'b']),
            put_select('y', help_text='Y column', options=['x', 'y']),
        ]), col=2, row=1),
            None,
        ],
        [span(put_image(img_link), col=2, row=1), put_scope('2-3')],
    ], cell_widths='33% 33% 33%')

    with use_scope('1-2'):
        put_html(gdp_chart('animation'))

    with use_scope('1-3'):
        put_html(gdp_chart('geo'))

    with use_scope('2-3'):
        put_markdown(md)
        put_input('something', label='input something to show as a toast message')
        put_button('submit', onclick=lambda: toast(pin.something))


if __name__ == '__main__':
    start_server(main, port=8080, debug=True)
"""


def print_coords(A, B):
    X, Z = data["X_val"], data["Z_val"]

    ns = "NS"[X < 0]  # True (1) defaults to "N" and False(0) defaults to "S"
    we = "EW"[Z < 0]  # True (1) defaults to "E" and False(0) defaults to "W

    return f"{abs(A):.2f}°{ns}, {abs(B):.2f}°{we}"


def print_input(data_dict):
    str = ""
    for x in data_dict:
        str += (f'{x}: {data_dict[x]} \n')
        #(f'Original array size: {arr.shape}')
    return str


data = input_group(
    "Input data for robot",
    [
        input("Input X", name="X_val", type=FLOAT),
        input("Input Z", name="Z_val", type=FLOAT),
        radio(
            "Which movement?",
            name="Movement",
            options=[
                "Bottom -> Top, Top -> Bottom",
                "Specific point",
                "Bottom -> Top, Bottom -> Top",
            ],
        ),
    ],
)

put_text(print_input(data))
