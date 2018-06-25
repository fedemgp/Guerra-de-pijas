set -e

function on_exit {
    kill -SIGINT $server_pid
    kill -9 $client1_pid
    kill -9 $client2_pid
}

trap on_exit INT TERM ERR

# launches the server in backgroung
./target/server 8888 ./res/test.yml &
server_pid=$!

# waits for the server to start
sleep 1

# starts a client in background
./target/client localhost 8888 ./res/test.yml &
client1_pid=$!

# starts the second client in background
./target/client localhost 8888 ./res/test.yml &
client2_pid=$!

set +e

# waits for both clients to close
wait $client1_pid
wait $client2_pid

sleep 1

# kills the server
kill -SIGINT $server_pid
