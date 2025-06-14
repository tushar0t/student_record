# Use official GCC image
# Use official GCC image
FROM gcc:latest

# Create working directory
WORKDIR /app

# Copy all files
COPY . .

# Compile your C++ program
RUN g++ -o app student_record.cpp

# Run the app
CMD ["./app"]
