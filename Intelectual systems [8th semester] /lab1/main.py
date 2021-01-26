import os
from bot import Bot
from dialogue_system import DialogueSystem, SimpleMatcher, RegexpMatcher
from console import run_console_dialogue

def get_dialogue_system():
    return DialogueSystem(
        # welcome/farawell
        SimpleMatcher('synonym(Bye) ...', 'Wait, you owe me $300!'),
        SimpleMatcher('synonym(Hello)', 'Hi', 'What\'s your name?', 'Long time no see'),
        SimpleMatcher('My name is $name', 'Nice to meet you {name}', 'Hi, {name}', 'Cool name!'),
        SimpleMatcher('My name is $name $surname+', 'Nice to meet you {name}', 'Is {surname} a surname? Or it\'s {name}?', 'Cool name! I have a friend whos name is {name} as well'),

        # pop-culture references
        SimpleMatcher('Hello there', 'General Kenobi', 'You are a Star Wars fan, right?'),
        SimpleMatcher('F', '*respect*'),
        
        # Opinions
        SimpleMatcher('What do you think any(of,about) any(me,you,him,her,them,yourself)', 'Tricky one.', 'I don\'t want to teel you that 🤫'),
        SimpleMatcher('What do you think any(of,about) $thing*', 'Well, I think {thing} is awful', 'Don\'t really have any opinion on that'),
        SimpleMatcher('Do you want me to $thing', 'What matters is what you want, not me', 'Why not?', 'if you won\'t, then I should probably $thing instead of you'),
        SimpleMatcher('Do you want ...', 'What matters is what you want, not me', 'Hm... idk'),

        # Response on opinion
        SimpleMatcher('I synonym(like) $thing+', 'Rly?', 'What else do you like?', 'So do I'),
        SimpleMatcher('I dont like $thing+', 'Rly?', 'What else you dislike?', 'So do I'),
        SimpleMatcher('I think $thing*', 'What makes you think in that way?', 'Thanks for sharing'),
        
        # Response on feeling/state
        SimpleMatcher('I am $something+', 'What makes you think so?', 'Is it a problem?', 'Do you want to share more?'),
        SimpleMatcher('Im thinking about? $something+', 'What makes you think so?', 'Such a big plan!', 'Do you want me to help you?'),
        SimpleMatcher('I want $something+', 'Come and get it!', 'Is it yours desire? Are you sure?'),
        SimpleMatcher('Im $something+', 'What makes you think so?', 'Is it a problem?', 'Do you want to share more?'),
        SimpleMatcher('I feel $something+', 'What makes you feel this way?', 'Is it a problem?', 'Well...?'),
        
        # suggestions
        SimpleMatcher('What if I $something+', 'Then..?', 'What would you feel if you {something}?'),
        SimpleMatcher('What if we $something+', 'You think we should {something}?'),
        
        
        # Random reactions
        SimpleMatcher('synonym(wow) ...', 'So cool', '😎'),
        SimpleMatcher('any(You,U) are? any(amazing,awesome)', 'Really?', 'Oh, please, stop it'),
        SimpleMatcher('any(Haha,hahaha,ahaha)', '😅', '☺️'),

        # story telling
        SimpleMatcher('If $something+ then $something_other+', 'Are you sure about such consequences?', 'Ok, but what if "{something_other}" won\'t happen? Is it a bad thing at all?'),
        # Other
        SimpleMatcher('any(Yes,No)', '✅✅', 'Ok then', 'Cool!'),
        SimpleMatcher('any(Yes,No) ...', '✅✅', 'Ok then', 'Cool!'),
        SimpleMatcher('any(Hm,hmm)', 'What are you thinking about?', 'Hm...?'),
        SimpleMatcher('any(rly,really)', 'No doubt!', 'Yeees', 'Sure!'),

        # General response in case of misunderstanding
        SimpleMatcher('*', 'Could you rephrase it? I did not follow', '🤷🏿‍♂️', '👽'),
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

