FROM python:3.12-slim

WORKDIR /app

COPY requirements.txt ./
COPY pipeline ./pipeline
COPY main.py .
COPY pipeline/api ./pipeline/api

ENV PYTHONPATH="/app"
ENV FLASK_APP=pipeline/api/app.py
ENV FLASK_RUN_HOST=0.0.0.0

RUN pip install --upgrade pip && \
    pip install -r requirements.txt

EXPOSE 5000

CMD ["flask", "run"]