PRAGMA foreign_keys = ON;
CREATE TABLE IF NOT EXISTS owners (
  id TEXT PRIMARY KEY,
  username TEXT UNIQUE NOT NULL,
  hash_password TEXT NOT NULL,
  first_name TEXT,
  last_name TEXT NOT NULL,
  phone TEXT NOT NULL,
  gender BOOLEAN NOT NULL DEFAULT(0)
);

-- INSERT INTO owners VALUES("1", "Nguyen Anh Nhat", "nhatvai123", "test", "test", "09092829", true);