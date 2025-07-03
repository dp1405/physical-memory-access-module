savedcmd_/home/ubuntu/driver_example/pmad.mod := printf '%s\n'   pmad.o | awk '!x[$$0]++ { print("/home/ubuntu/driver_example/"$$0) }' > /home/ubuntu/driver_example/pmad.mod
