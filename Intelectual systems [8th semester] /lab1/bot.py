import typing as t
import logging

from telegram import Update
from telegram.ext import Updater, CommandHandler, MessageHandler, Filters, CallbackContext

# Enable logging
logging.basicConfig(
    format='%(asctime)s - %(name)s - %(levelname)s - %(message)s', level=logging.INFO
)

logger = logging.getLogger(__name__)


def start(update: Update, context: CallbackContext) -> None:
    update.message.reply_text('Hi!')


def help_command(update: Update, context: CallbackContext) -> None:
    update.message.reply_text('Just write me something :)')


def echo(update: Update, context: CallbackContext) -> None:
    update.message.reply_text(update.message.text)


class Bot:
    updater: Updater
    def __init__(self, token: str, text_handler: t.Callable[[str], str] = lambda s: s):    
        self.updater = Updater(token, use_context=True)
        self._text_handler = text_handler

        dispatcher = self.updater.dispatcher
        dispatcher.add_handler(CommandHandler("start", self.handle_start))
        dispatcher.add_handler(CommandHandler("help", self.handle_help_command))

        dispatcher.add_handler(MessageHandler(Filters.text & ~Filters.command, self.handle_text))

    def run(self):
        self.updater.start_polling()
        self.updater.idle()

    def handle_text(self, update: Update, context: CallbackContext):
        reply = self._text_handler(update.message.text)
        update.message.reply_text(reply)

    def handle_start(self, update: Update, context: CallbackContext):
        update.message.reply_text('Hi!')
    
    def handle_help_command(self, update: Update, context: CallbackContext):
        update.message.reply_text('Just write me something :)')
        
    