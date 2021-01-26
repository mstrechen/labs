all: build stop run

all-shell: build run-shell

build:
	docker build . -t is-lab-1

run:
	docker run -d --rm --env-file=env.txt --name=is-lab-1-bot is-lab-1

run-shell:
	docker run -it --rm --env-file=env.txt is-lab-1

stop:
	docker stop -f is-lab-1-bot 2>/dev/null || echo "Already stopped"