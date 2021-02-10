FROM python:3.8-buster

RUN apt-get update && apt-get install -y software-properties-common
RUN apt-add-repository ppa:swi-prolog/stable && apt-get install -y swi-prolog

WORKDIR /app
COPY requirements.txt .
RUN pip install -r requirements.txt

COPY . /app
ENTRYPOINT ["python", "main.py"]