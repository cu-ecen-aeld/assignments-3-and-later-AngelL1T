
#!/bin/sh


if [ $# -ne 2 ]; then
	echo "Error: Invalid number of arguments."
	echo "Usage: $0 <writefile> <writestr>"
	exit 1
fi

writefile="$1"
writestr="$2"

mkdir -p "$(dirname "$writefile")"

if ! echo "$writestr" > "$writefile" 2>/dev/null; then
	echo "Error: File could not be created at $writefile"
	exit 1
fi

