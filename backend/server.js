/**
 * Transpiler Backend Server
 * 
 * Tries to use the compiled C transpiler binary first.
 * Falls back to the JavaScript-based transpiler if the binary is not available.
 */

const express = require('express');
const cors = require('cors');
const fs = require('fs');
const path = require('path');
const { execFile } = require('child_process');
const { transpile } = require('./transpiler');

const app = express();
const PORT = 3001;

app.use(cors());
app.use(express.json({ limit: '1mb' }));

// Check if the C transpiler binary exists
function getTranspilerPath() {
    const paths = [
        path.join(__dirname, '..', 'compiler', 'transpiler.exe'),
        path.join(__dirname, '..', 'compiler', 'transpiler'),
    ];
    for (const p of paths) {
        if (fs.existsSync(p)) return p;
    }
    return null;
}

// Use C binary transpiler
function transpileWithBinary(code, target) {
    return new Promise((resolve, reject) => {
        const binaryPath = getTranspilerPath();
        if (!binaryPath) {
            reject(new Error('Binary not found'));
            return;
        }

        const inputPath = path.join(__dirname, '..', 'input.txt');
        fs.writeFileSync(inputPath, code);

        execFile(binaryPath, ['--json', '--target', target, inputPath], {
            timeout: 10000,
        }, (error, stdout, stderr) => {
            try {
                const result = JSON.parse(stdout);
                resolve(result);
            } catch (e) {
                reject(new Error(stderr || stdout || 'Transpiler failed'));
            }
        });
    });
}

// POST /transpile
app.post('/transpile', async (req, res) => {
    const { code, target = 'python' } = req.body;

    if (!code || typeof code !== 'string') {
        return res.status(400).json({ 
            success: false, 
            errors: [{ line: 0, message: 'No code provided' }] 
        });
    }

    // Try compiled binary first
    const binaryPath = getTranspilerPath();
    if (binaryPath) {
        try {
            const result = await transpileWithBinary(code, target);
            // console.log(result);
            return res.json(result);
        } catch (err) {
            console.log('Binary transpiler failed, using JS fallback:', err.message);
        }
    }

    // Use JavaScript transpiler fallback
    try {
        const result = transpile(code, target);
        return res.json(result);
    } catch (err) {
        return res.status(500).json({
            success: false,
            errors: [{ line: 0, message: err.message }],
        });
    }
});

// GET /health
app.get('/health', (req, res) => {
    const binaryAvailable = !!getTranspilerPath();
    res.json({ 
        status: 'ok', 
        mode: binaryAvailable ? 'native' : 'javascript',
        message: binaryAvailable 
            ? 'Using compiled C transpiler' 
            : 'Using JavaScript fallback transpiler'
    });
});

app.listen(PORT, () => {
    const binaryAvailable = !!getTranspilerPath();
    console.log(`\n🚀 Transpiler Backend running at http://localhost:${PORT}`);
    console.log(`📦 Mode: ${binaryAvailable ? 'Native C binary' : 'JavaScript fallback'}`);
    console.log(`\nEndpoints:`);
    console.log(`  POST /transpile   - Transpile code`);
    console.log(`  GET  /health      - Check server status\n`);
});
