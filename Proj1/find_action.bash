echo "Enter apt number (format: APT-xx)"
read apt

file=(./Data/*)
total=${#file[@]}
index=0
while [ "$index" -lt "$total" ]; do
	if grep -q "$apt" ${file[$index]}; then
		read -a token -d EOF < ${file[$index]}
		echo "Email: ${token[0]}"
		echo "Name: ${token[1]} ${token[2]}"
		echo "Apt: ${token[3]}"
		echo "Balance: ${token[5]}"
		echo "Rent Amt: ${token[4]}"
		echo "Due Date: ${token[6]}"
	fi
	((index++))
done
if ! grep -q "$apt" ./Data/*; then
	echo "Error: apartment number not found"
fi