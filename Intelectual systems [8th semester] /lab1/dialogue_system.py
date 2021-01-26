import typing as t
import re
import random
import nltk 

nltk.download('wordnet')
from nltk.corpus import wordnet


class PhraseMatcher:
  compiled_re: 're.Pattern'
  responses: t.Tuple[str, ...]

  def match(self, text: str) -> t.Optional[t.Tuple[t.Tuple[str, ...], t.Dict[str, t.Any]]]: # matched groups
    text = ' '.join(text.strip().split())
    res = self.compiled_re.fullmatch(text)
    if not res:
      return None
    return res.groups(), res.groupdict()
  
  def get_response(self, positional_matches: t.Tuple[str, ...], non_positional_matches: t.Dict[str, t.Any]) -> str:
    response_template = random.choice(self.responses)
    return response_template.format(*positional_matches, **non_positional_matches)


class RegexpMatcher(PhraseMatcher):
  def __init__(self, pattern: str, *responses):
    self.compiled_re = re.compile(pattern, re.IGNORECASE)
    self.responses = responses


class SimpleMatcher(PhraseMatcher):
  WILDCARD_RE = re.compile('(?:\.\.\.|\*)')
  FUNC_RE = re.compile('(?P<func>\w+)\((?P<args>\s*\w+(?:\s*,\s*\w+)*)\)')
  ARG_RE = re.compile('\$\w+[\+\*\?]?')
  WORD_RE = re.compile('\w+')
  
  def __init__(self, pattern: t.Union[str, t.Collection[str]], *responses):
    self.regexp = self._compile_pattern(pattern)
    self.compiled_re = re.compile(self.regexp, re.IGNORECASE)
    self.responses = responses
  
  @classmethod
  def _compile_pattern(cls, pattern: t.Union[str, t.Collection[str]]):
    if isinstance(pattern, str):
      pattern = pattern.split()
    parts = [cls._compile_pattern_part(pattern_part) for pattern_part in pattern]
    return ' '.join(parts)
  
  @classmethod
  def _compile_pattern_part(cls, pattern: str): 
    if cls.WILDCARD_RE.fullmatch(pattern):
      return cls._compile_wildcard(pattern)
    if cls.FUNC_RE.fullmatch(pattern):
      return cls._compile_func(pattern)
    if cls.ARG_RE.fullmatch(pattern):
      return cls._compile_arg(pattern)
    if cls.WORD_RE.fullmatch(pattern):
      return cls._compile_word(pattern)
    raise ValueError("Unknown pattern syntax", pattern)
  
  @classmethod
  def _compile_wildcard(cls, pattern: str) -> str:
    return '(?:\w+(?: \w+)*)?'
  
  def _compile_synonyms(*args) -> str:
    synonyms = set()

    for word in args:
      for syn in wordnet.synsets(word):
        for l in syn.lemmas():
          synonyms.add(l.name().replace('_', ' '))
    return f'(?:{"|".join(synonyms)})'
  
  
  def _compile_antonyms(*args) -> str:
    antonyms = set()

    for word in args:
      for syn in wordnet.synsets(word):
        for l in syn.lemmas():
          for ant in l.antonyms():
            antonyms.add(ant.name().replace('_', ' '))
    return f'(?:{"|".join(antonyms)})'
  
  FUNC_MAPPING = {
      'any': lambda *args: f'(?:{"|".join(args)})',
      'syn': _compile_synonyms,
      'synonym': _compile_synonyms,
      'ant': _compile_antonyms,
      'antonym': _compile_antonyms,
  }

  @classmethod
  def _compile_func(cls, pattern: str) -> str:
    match = cls.FUNC_RE.fullmatch(pattern)
    func = match.group('func').strip()
    args = [arg.strip() for arg in match.group('args').split(',')]
    return cls.FUNC_MAPPING[func](*args)

  @classmethod
  def _compile_arg(cls, pattern: str) -> str:
    name = pattern[1:]
    case = '' 
    if name[-1] in ['?', '*', '+']:
      case = name[-1]
      name = name[:-1]
    if case in ['?', '']:
      return f'(?P<{name}>(?:\w+){case})'
    if case == '*':
      return f'(?P<{name}>(?:\w+)?(?: \w+)*)'
    if case == '+':
      return f'(?P<{name}>(?:\w+)(?: \w+)*)'
    raise ValueError("Unknow variable syntax", pattern)
  
  @classmethod
  def _compile_word(cls, pattern: str) -> str:
    return pattern

import string
class DialogueSystem:
  def __init__(self, *rules: t.Tuple[PhraseMatcher]):
    self.rules = rules
  
  ALLOWED_SYMBOLS = string.ascii_letters + string.digits + ' '
  def get_response(self, text) -> str:
    text = ''.join(filter(lambda s: s in self.ALLOWED_SYMBOLS, text))
    for rule in self.rules:
      match = rule.match(text)
      if match:
        return rule.get_response(*match)
    return "I dunno lol."
