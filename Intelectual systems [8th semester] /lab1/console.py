import typing as t

def run_console_dialogue(get_response: t.Callable[[str], str]):
    print("BOT: Hi!")
    while True:
        message = input("ME : ")
        response = get_response(message)
        print("BOT:", response)

    