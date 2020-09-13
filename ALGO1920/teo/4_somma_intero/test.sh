for i in input*; do
 ./1a < ${i} | diff -q - output${i##input};
done
