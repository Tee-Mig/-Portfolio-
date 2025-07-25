CREATE TABLE players (
  player_id SERIAL PRIMARY KEY,
  name VARCHAR(255) UNIQUE NOT NULL
);

CREATE TABLE matches (
  match_id SERIAL PRIMARY KEY,
  tourney_id VARCHAR(50),
  tourney_name VARCHAR(255),
  surface VARCHAR(50),
  tourney_level VARCHAR(10),
  tourney_date DATE,
  match_num INT,
  round VARCHAR(50),
  score TEXT,
  minutes INT,
  w_ace INT,
  w_df INT,
  w_1stIn INT,
  w_1stWon INT,
  w_bpSaved INT,
  w_bpFaced INT,
  l_ace INT,
  l_df INT,
  l_1stIn INT,
  l_1stWon INT,
  l_bpSaved INT,
  l_bpFaced INT,
  winner_rank INT,
  loser_rank INT
  winner_id INT REFERENCES players(player_id),
  loser_id INT REFERENCES players(player_id),
);