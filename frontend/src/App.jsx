import { useState, useCallback } from 'react'
import Editor from '@monaco-editor/react'
import axios from 'axios'

const SAMPLE_CODE = `// Welcome to TranspilerX — Java to C/Python!
// Write your Java code and transpile it.

public class Calculator {

    public static int add(int a, int b) {
        return a + b;
    }

    public static int factorial(int n) {
        int result = 1;
        for (int i = 1; i <= n; i++) {
            result *= i;
        }
        return result;
    }

    public static void main(String[] args) {
        int sum = add(10, 20);
        System.out.println(sum);

        int product = 5 * 6;
        System.out.println(product);

        if (sum > 25) {
            System.out.println("Sum is large!");
        } else {
            System.out.println("Sum is small.");
        }

        int counter = 0;
        while (counter < 3) {
            System.out.println(counter);
            counter = counter + 1;
        }

        int fact = factorial(5);
        System.out.println(fact);
    }
}
`

const API_URL = 'http://localhost:3001'

function ASTTreeView({ node, depth = 0 }) {
    if (!node) return null

    const renderValue = () => {
        switch (node.type) {
            case 'IntLit':
            case 'DoubleLit': return <span className="ast-value">{node.value}</span>
            case 'String': return <span className="ast-value">{node.value}</span>
            case 'CharLit': return <span className="ast-value">'{node.value}'</span>
            case 'Bool': return <span className="ast-value">{String(node.value)}</span>
            case 'Identifier': return <span className="ast-name">{node.name}</span>
            case 'BinOp':
            case 'UnaryOp': return <span className="ast-op">{node.op}</span>
            case 'VarDecl':
            case 'Assign':
            case 'ClassDecl':
            case 'MethodDecl':
            case 'FuncCall':
            case 'MethodCall':
            case 'TypedParam':
            case 'ArrayAccess': return (
                <span className="ast-name">
                    {node.name}
                    {node.javaType && <span className="ast-jtype"> : {node.javaType}</span>}
                </span>
            )
            case 'Cast':
            case 'NewArray': return (
                <span className="ast-jtype">({node.javaType})</span>
            )
            default: return null
        }
    }

    return (
        <div className="ast-node" style={{ paddingLeft: depth > 0 ? 20 : 0 }}>
            <div className="ast-label">
                <span className="ast-type">{node.type}</span>
                {renderValue()}
            </div>
            {node.left && <ASTTreeView node={node.left} depth={depth + 1} />}
            {node.right && <ASTTreeView node={node.right} depth={depth + 1} />}
            {node.body && <ASTTreeView node={node.body} depth={depth + 1} />}
            {node.init && <ASTTreeView node={node.init} depth={depth + 1} />}
            {node.update && <ASTTreeView node={node.update} depth={depth + 1} />}
            {node.items && node.items.map((item, i) => (
                <ASTTreeView key={i} node={item} depth={depth + 1} />
            ))}
        </div>
    )
}

function App() {
    const [code, setCode] = useState(SAMPLE_CODE)
    const [target, setTarget] = useState('python')
    const [result, setResult] = useState(null)
    const [loading, setLoading] = useState(false)
    const [activeTab, setActiveTab] = useState('output')
    const [serverMode, setServerMode] = useState(null)

    const handleTranspile = useCallback(async () => {
        if (!code.trim()) return
        setLoading(true)
        try {
            const response = await axios.post(`${API_URL}/transpile`, { code, target })
            setResult(response.data)
            if (response.data.success) {
                setActiveTab('output')
            } else {
                setActiveTab('errors')
            }
        } catch (err) {
            setResult({
                success: false,
                errors: [{
                    line: 0,
                    message: err.response?.data?.errors?.[0]?.message || 'Failed to connect to backend. Make sure the server is running on port 3001.'
                }],
                tokens: [],
                ast: null,
                symbols: [],
                output: null
            })
            setActiveTab('errors')
        } finally {
            setLoading(false)
        }
    }, [code, target])

    const errorCount = result?.errors?.length || 0
    const tokenCount = result?.tokens?.length || 0

    return (
        <div className="app">
            {/* Header */}
            <header className="header">
                <div className="logo">
                    <div className="logo-icon">⚡</div>
                    <span className="logo-text">TranspilerX</span>
                    <span className="logo-tag">Java → C / Python</span>
                </div>
                <div className="header-controls">
                    <div className="target-selector">
                        <button
                            className={`target-btn ${target === 'python' ? 'active' : ''}`}
                            onClick={() => setTarget('python')}
                        >
                            🐍 Python
                        </button>
                        <button
                            className={`target-btn ${target === 'c' ? 'active' : ''}`}
                            onClick={() => setTarget('c')}
                        >
                            ⚙️ C
                        </button>
                    </div>
                    <button
                        className="btn btn-primary"
                        onClick={handleTranspile}
                        disabled={loading || !code.trim()}
                        id="transpile-btn"
                    >
                        {loading ? (
                            <>
                                <div className="spinner" />
                                Transpiling...
                            </>
                        ) : (
                            <>▶ Transpile</>
                        )}
                    </button>
                </div>
            </header>

            {/* Main Content */}
            <div className="main-content">
                {/* Left Panel - Code Editor */}
                <div className="panel panel-left">
                    <div className="panel-header">
                        <div className="panel-title">
                            <span className="dot" />
                            Source Code
                        </div>
                        <span style={{ fontSize: 11, color: 'var(--text-muted)' }}>
                            Java
                        </span>
                    </div>
                    <div className="panel-body">
                        <Editor
                            height="100%"
                            defaultLanguage="java"
                            theme="vs-dark"
                            value={code}
                            onChange={(v) => setCode(v || '')}
                            options={{
                                fontSize: 14,
                                fontFamily: "'JetBrains Mono', monospace",
                                minimap: { enabled: false },
                                padding: { top: 16, bottom: 16 },
                                lineNumbers: 'on',
                                roundedSelection: true,
                                scrollBeyondLastLine: false,
                                automaticLayout: true,
                                tabSize: 4,
                                renderLineHighlight: 'all',
                                cursorBlinking: 'smooth',
                                cursorSmoothCaretAnimation: 'on',
                                smoothScrolling: true,
                                bracketPairColorization: { enabled: true },
                            }}
                        />
                    </div>
                </div>

                {/* Right Panel - Output */}
                <div className="panel panel-right">
                    <div className="tabs">
                        <button
                            className={`tab ${activeTab === 'output' ? 'active' : ''}`}
                            onClick={() => setActiveTab('output')}
                        >
                            📄 Output
                        </button>
                        <button
                            className={`tab ${activeTab === 'errors' ? 'active' : ''}`}
                            onClick={() => setActiveTab('errors')}
                        >
                            ⚠️ Errors {errorCount > 0 && `(${errorCount})`}
                        </button>
                        <button
                            className={`tab ${activeTab === 'tokens' ? 'active' : ''}`}
                            onClick={() => setActiveTab('tokens')}
                        >
                            🔤 Tokens {tokenCount > 0 && `(${tokenCount})`}
                        </button>
                        <button
                            className={`tab ${activeTab === 'ast' ? 'active' : ''}`}
                            onClick={() => setActiveTab('ast')}
                        >
                            🌳 AST
                        </button>
                        <button
                            className={`tab ${activeTab === 'symbols' ? 'active' : ''}`}
                            onClick={() => setActiveTab('symbols')}
                        >
                            📋 Symbols
                        </button>
                    </div>

                    <div className="panel-body">
                        {/* Output Tab */}
                        {activeTab === 'output' && (
                            result?.output ? (
                                <div className="code-output">{result.output}</div>
                            ) : (
                                <div className="empty-state">
                                    <div className="empty-state-icon">☕</div>
                                    <div className="empty-state-text">
                                        Click <strong>Transpile</strong> to convert<br />
                                        Java code to {target === 'python' ? 'Python' : 'C'}
                                    </div>
                                </div>
                            )
                        )}

                        {/* Errors Tab */}
                        {activeTab === 'errors' && (
                            errorCount > 0 ? (
                                <div className="errors-list">
                                    {result.errors.map((err, i) => (
                                        <div key={i} className="error-item">
                                            <span className="error-icon">✕</span>
                                            <div>
                                                {err.line > 0 && (
                                                    <div className="error-line">Line {err.line}</div>
                                                )}
                                                <div className="error-message">{err.message}</div>
                                            </div>
                                        </div>
                                    ))}
                                </div>
                            ) : (
                                <div className="empty-state">
                                    <div className="empty-state-icon">✅</div>
                                    <div className="empty-state-text">
                                        {result ? 'No errors found!' : 'Errors will appear here after transpilation'}
                                    </div>
                                </div>
                            )
                        )}

                        {/* Tokens Tab */}
                        {activeTab === 'tokens' && (
                            tokenCount > 0 ? (
                                <div className="token-grid">
                                    {result.tokens.map((tok, i) => (
                                        <div key={i} className="token-item">
                                            <span className="token-type">{tok.type}</span>
                                            <span className="token-value">{String(tok.value)}</span>
                                            <span className="token-line">Line {tok.line}</span>
                                        </div>
                                    ))}
                                </div>
                            ) : (
                                <div className="empty-state">
                                    <div className="empty-state-icon">🔤</div>
                                    <div className="empty-state-text">
                                        Tokens will appear here after transpilation
                                    </div>
                                </div>
                            )
                        )}

                        {/* AST Tab */}
                        {activeTab === 'ast' && (
                            result?.ast ? (
                                <div className="ast-tree">
                                    <ASTTreeView node={result.ast} />
                                </div>
                            ) : (
                                <div className="empty-state">
                                    <div className="empty-state-icon">🌳</div>
                                    <div className="empty-state-text">
                                        Abstract Syntax Tree will appear here after transpilation
                                    </div>
                                </div>
                            )
                        )}

                        {/* Symbols Tab */}
                        {activeTab === 'symbols' && (
                            result?.symbols?.length > 0 ? (
                                <div className="symbol-table">
                                    <table>
                                        <thead>
                                            <tr>
                                                <th>Name</th>
                                                <th>Kind</th>
                                                <th>Java Type</th>
                                                <th>Params</th>
                                                <th>Line</th>
                                            </tr>
                                        </thead>
                                        <tbody>
                                            {result.symbols.map((sym, i) => (
                                                <tr key={i}>
                                                    <td style={{ color: 'var(--text-accent)' }}>{sym.name}</td>
                                                    <td>
                                                        <span className={`sym-type ${sym.type}`}>
                                                            {sym.type}
                                                        </span>
                                                    </td>
                                                    <td style={{ color: 'var(--warning)' }}>{sym.javaType || '—'}</td>
                                                    <td style={{ color: 'var(--text-muted)' }}>{sym.params}</td>
                                                    <td style={{ color: 'var(--text-muted)' }}>{sym.line}</td>
                                                </tr>
                                            ))}
                                        </tbody>
                                    </table>
                                </div>
                            ) : (
                                <div className="empty-state">
                                    <div className="empty-state-icon">📋</div>
                                    <div className="empty-state-text">
                                        Symbol table will appear here after transpilation
                                    </div>
                                </div>
                            )
                        )}
                    </div>
                </div>
            </div>

            {/* Status Bar */}
            <div className="status-bar">
                <div className="status-item">
                    <span className={`status-dot ${result ? (result.success ? 'success' : 'error') : 'idle'}`} />
                    {result
                        ? (result.success ? 'Transpilation successful' : `${errorCount} error${errorCount !== 1 ? 's' : ''} found`)
                        : 'Ready'}
                </div>
                <div style={{ display: 'flex', gap: 16 }}>
                    <span className="status-item">Source: Java</span>
                    <span className="status-item">Target: {target === 'python' ? 'Python' : 'C'}</span>
                    <span className="status-item">Powered by Flex + Bison</span>
                </div>
            </div>
        </div>
    )
}

export default App
