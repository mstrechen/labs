import os
from bot import Bot
from dialogue_system import DialogueSystem, SimpleMatcher
from console import run_console_dialogue

def get_dialogue_system():
    return DialogueSystem(
        SimpleMatcher('synonym(wow) ...', 'So cool', '😎'),
        SimpleMatcher('Hello there', 'General Kenobi', 'You are a Star Wars fan, right?'),
        SimpleMatcher('any(You,U) $maybe_are? any(amazing,awesome)', 'Really?', 'Oh, please, stop it'),
        SimpleMatcher('What do you think about $thing*', 'Well, I think {thing} is awful', 'Don\'t really have any opinion on that'),
        SimpleMatcher('Haha', '😅', '☺️'),
        SimpleMatcher('synonym(Bye)', 'Wait, you owe me $300!'),
        SimpleMatcher('synonym(Hello)', 'Hi', 'What\'s your name?'),
        SimpleMatcher('My name is $name+', 'Nice to meet you {name}', 'Hi, {name}', 'Cool name!'),
        SimpleMatcher('*', '😈', '🤷🏿‍♂️', '👽'),
        SimpleMatcher('I synonym(love) $thing*', 'Rly?')
    )

if __name__ == '__main__':
    ds = get_dialogue_system()
    token = os.getenv('TG_TOKEN')
    print(token, flush=True)
    if token:
        bot = Bot(token=token, text_handler=ds.get_response)
        bot.run()
    else:
        run_console_dialogue(ds.get_response)

