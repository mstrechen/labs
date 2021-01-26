## Simple factual dialogue system

Pattern matching & pattern magic 

### Console UI usage

Use `make all-shell` for a quickstart with console UI.

Write phrase, get response - nothing too hard.

### Telegram bot

Get a bot token from [BotFather](https://t.me/BotFather), put it into `env.dummy.txt`, rename it to `env.txt` and run `make` or `make all`.

### Rules

You can use `RegexpMatcher` or `SimpleMatcher` to setup response rules. Simple matcher in fact isn't that simple, but at least has a more human-readable syntax.

Some examples:
```python
# Simple word-by-word match. First arguments stands for pattern, all the following - possible responses (will be picked randomly)
RegexpMatcher('Wow so cool', 'Yes, I agree', 'Yep')
# Wildcards - match any sequence of words
RegexpMatcher('Wow ... cool', 'Yes, I agree', 'Yep')
RegexpMatcher('Wow * cool', 'Yes, I agree', 'Yep')
# Some functions
RegexpMatcher('synonym(amazing)', 'Yes, it is', 'Yeeeees')
RegexpMatcher('antonym(cool)', 'Yes, it\'s pretty warm outside')
RegexpMatcher('any(you,u)', 'I\'m what?')


# Variables - could be used in responses
# Would match "I'm Mark", but not "I'm Bill Gates"
RegexpMatcher('Im $name', 'Hi {name}')
# Would match "I'm Mark" as well as "I'm Mark Zuck", but not "I'm"
RegexpMatcher('Im $name+', 'Hi {name}')
# Would match "I'm Mark" as well as  "I'm", but not "I'm Mark Zuck"
RegexpMatcher('Im $name?', 'Hi {name}')
# Would match "I'm Mark" as well as  "I'm" and "I'm Mark Zuck"
RegexpMatcher('Im $name*', 'Hi {name}')
# Multiple variables are allowed as well
RegexpMatcher('Im $name+ from $country+', 'Hello {name}. I have never been in {country}, is it cool there?')
```

Notes: 
- Matching is case insensitive
- All special characters are filtered out, as well as double spaces etc. So for `Wow,   so     cool! 👽` you should expect `Wow so cool`
- Order matters - the arlier the rule is written, the earlier it is checked and applied
- Matching is performed on the whole phrase, i.e. you should write `Wow ...`, not `Wow` if you want to match `Wow so cool`
