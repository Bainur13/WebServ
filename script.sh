#!/bin/bash

for i in {1..100}
do
    curl -s http://localhost:8080 &
done

wait
