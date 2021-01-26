FROM python:3.7.9-buster

COPY requirements.txt .
RUN pip install --user -r requirements.txt && \
    rm -f requirements.txt
RUN python -c "import nltk; nltk.download('wordnet')"

COPY *.py /app/
WORKDIR /app

CMD ["python", "main.py"]
