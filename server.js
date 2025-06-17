const express = require('express');
const mysql = require('mysql2/promise');
const bodyParser = require('body-parser');
const cors = require('cors');
require('dotenv').config();

const app = express();
const port = 3000;

// Middleware
app.use(cors());
app.use(bodyParser.json());

// MySQL Connection Pool
const pool = mysql.createPool({
  host: process.env.DB_HOST,
  port: process.env.DB_PORT,
  user: process.env.DB_USER,
  password: process.env.DB_PASSWORD,
  database: process.env.DB_DATABASE,
  ssl: {
    rejectUnauthorized: true,
    ca: process.env.DB_CA
  }
});

// Create students table if not exists
async function initializeDatabase() {
  try {
    const createTableQuery = `
      CREATE TABLE IF NOT EXISTS students (
        id INT AUTO_INCREMENT PRIMARY KEY,
        name VARCHAR(255) NOT NULL,
        phone VARCHAR(20),
        email VARCHAR(255),
        studentID INT NOT NULL UNIQUE,
        universityRoll INT,
        course VARCHAR(255),
        section VARCHAR(10),
        rollNumber INT,
        marks10 DECIMAL(5,2),
        marks12 DECIMAL(5,2),
        scholarType ENUM('Day Scholar', 'Hostler'),
        additionalInfo VARCHAR(255),
        hostelRoom VARCHAR(50)
      )
    `;
    
    await pool.query(createTableQuery);
    console.log('Students table initialized');
  } catch (err) {
    console.error('Error initializing database:', err);
  }
}

// Add a student
app.post('/students', async (req, res) => {
  try {
    const student = req.body;
    const [result] = await pool.query('INSERT INTO students SET ?', student);
    res.status(201).json({ message: 'Student added successfully', id: result.insertId });
  } catch (err) {
    console.error('Error adding student:', err);
    res.status(500).json({ error: 'Failed to add student' });
  }
});

// Get all students
app.get('/students', async (req, res) => {
  try {
    const [rows] = await pool.query('SELECT * FROM students');
    res.json(rows);
  } catch (err) {
    console.error('Error fetching students:', err);
    res.status(500).json({ error: 'Failed to fetch students' });
  }
});

// Delete a student
app.delete('/students/:studentID', async (req, res) => {
  try {
    const studentID = req.params.studentID;
    const [result] = await pool.query('DELETE FROM students WHERE studentID = ?', [studentID]);
    
    if (result.affectedRows === 0) {
      return res.status(404).json({ error: 'Student not found' });
    }
    
    res.json({ message: 'Student deleted successfully' });
  } catch (err) {
    console.error('Error deleting student:', err);
    res.status(500).json({ error: 'Failed to delete student' });
  }
});

// Get statistics
app.get('/stats', async (req, res) => {
  try {
    // Get total students
    const [totalResult] = await pool.query('SELECT COUNT(*) as total FROM students');
    const total = totalResult[0].total;
    
    // Get day scholars count
    const [dayResult] = await pool.query("SELECT COUNT(*) as count FROM students WHERE scholarType = 'Day Scholar'");
    const dayScholars = dayResult[0].count;
    
    // Get hostlers count
    const [hostlerResult] = await pool.query("SELECT COUNT(*) as count FROM students WHERE scholarType = 'Hostler'");
    const hostlers = hostlerResult[0].count;
    
    // Get average marks
    const [avg10Result] = await pool.query('SELECT AVG(marks10) as avg FROM students');
    const avgMarks10 = parseFloat(avg10Result[0].avg || 0).toFixed(1);
    
    const [avg12Result] = await pool.query('SELECT AVG(marks12) as avg FROM students');
    const avgMarks12 = parseFloat(avg12Result[0].avg || 0).toFixed(1);
    
    // Get top student
    const [topResult] = await pool.query(`
      SELECT name, (COALESCE(marks10,0) + COALESCE(marks12,0)) as totalMarks 
      FROM students 
      ORDER BY totalMarks DESC 
      LIMIT 1
    `);
    const topStudent = topResult[0] ? topResult[0].name : null;
    
    res.json({
      total,
      dayScholars,
      hostlers,
      avgMarks10,
      avgMarks12,
      topStudent
    });
  } catch (err) {
    console.error('Error fetching statistics:', err);
    res.status(500).json({ error: 'Failed to fetch statistics' });
  }
});

// Start the server
app.listen(port, async () => {
  console.log(`Server running on http://localhost:${port}`);
  await initializeDatabase();
});