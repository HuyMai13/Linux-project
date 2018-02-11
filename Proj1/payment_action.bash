echo "Enter email"
read email
echo "Enter payment amt"
read amt
amt=${amt%.*}

cd ./Data
if [ -e "$email" ]; then
	read -a token -d EOF < $email
	token[5]=${token[5]%.*}
	((token[5]+=$amt))
	echo -e "${token[0]} ${token[1]} ${token[2]}\n${token[3]} ${token[4]} ${token[5]} ${token[6]}" > $email
else
	echo "Error: customer not found"
fi
