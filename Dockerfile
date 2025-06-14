# Use the official GCC image as base
FROM gcc:latest

# Set the working directory
WORKDIR /app

# Copy the C++ file into the container
COPY student_record.cpp .

# Compile the C++ code
RUN g++ -o student_app student_record.cpp

# Run the compiled program
CMD ["./student_app"]