

for N in "${@}" ;
do
  echo ${N}
done

echo ""
echo "$1"
echo "${@:2:3}"
echo "${@:2:$#}"

