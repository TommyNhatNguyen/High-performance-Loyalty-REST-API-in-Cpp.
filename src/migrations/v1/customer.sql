CREATE TABLE IF NOT EXISTS customers (
    id TEXT PRIMARY KEY,
    name TEXT,
    phone TEXT UNIQUE,
    description TEXT,
    gender INT NOT NULL
);
