-- User --------------------------------------------------

CREATE TABLE IF NOT EXISTS user (
    user_id INTEGER PRIMARY KEY, 
    u_name VARCHAR(50) NOT NULL, 
    email VARCHAR(100) NOT NULL, 
    password_hash VARCHAR(97) NOT NULL,
    CONSTRAINT uq_user_name UNIQUE(u_name),
    CONSTRAINT uq_user_email UNIQUE(email)
);

-- Animes --------------------------------------------------

CREATE TABLE IF NOT EXISTS anime (
    anime_id INTEGER PRIMARY KEY, 
    title_jap TEXT NOT NULL, 
    title_romanji TEXT NOT NULL, 
    title_eng TEXT DEFAULT "No english title", 
    summary TEXT NOT NULL,
    number_of_episodes INTEGER NOT NULL,
    status_of_publication INTEGER NOT NULL,
    publication_date DATE NOT NULL, 
    franchise INTEGER,
    myanimelist_link VARCHAR(500) NOT NULL,
    CONSTRAINT valid_status_of_pub CHECK (status_of_pub IN (0, 1, 2, 3)),
    FOREIGN KEY (franchise) REFERENCES franchise(franchise_id) ON DELETE SET NULL
);


-- Mangas --------------------------------------------------

CREATE TABLE IF NOT EXISTS manga (
    manga_id INTEGER PRIMARY KEY, 
    isbn VARCHAR(13) NOT NULL,
    title_jap TEXT NOT NULL, 
    title_romanji TEXT NOT NULL,  
    title_eng TEXT DEFAULT "No english title", 
    summary TEXT NOT NULL,
    number_of_chapters INTEGER NOT NULL,
    number_of_volumes INTEGER NOT NULL,
    status_of_publication INTEGER NOT NULL,
    publication_date DATE NOT NULL,
    franchise INTEGER,
    mangadex_link VARCHAR(500) NOT NULL,
    CONSTRAINT uq_isbn UNIQUE (isbn),
    CONSTRAINT valid_status_of_pub CHECK (status_of_pub IN (0, 1, 2, 3)),
    FOREIGN KEY (franchise) REFERENCES franchise(franchise_id) ON DELETE SET NULL
);

-- Visual Novels --------------------------------------------------

CREATE TABLE IF NOT EXISTS visual_novel (
    visual_novel_id INTEGER PRIMARY KEY, 
    isbn VARCHAR(13) NOT NULL,
    title_jap TEXT NOT NULL, 
    title_romanji TEXT NOT NULL, 
    title_eng TEXT DEFAULT "No english title", 
    summary TEXT NOT NULL,
    publication_date DATE NOT NULL,
    franchise INTEGER,
    visual_novel_db_link VARCHAR(500) NOT NULL,
    FOREIGN KEY (franchise) REFERENCES franchise(franchise_id) ON DELETE SET NULL
);


-- Light Novels --------------------------------------------------

CREATE TABLE IF NOT EXISTS light_novel (
    light_novel_id INTEGER PRIMARY KEY, 
    title_jap TEXT NOT NULL, 
    title_romanji TEXT NOT NULL, 
    title_eng TEXT DEFAULT "No english title", 
    status_of_publication INTEGER NOT NULL,
    publication_date DATE NOT NULL,
    summary TEXT NOT NULL,
    franchise INTEGER, 
    light_novel_db_link VARCHAR(500) NOT NULL,
    CONSTRAINT uq_isbn UNIQUE (isbn),
    CONSTRAINT valid_status_of_pub CHECK (status_of_pub IN (0, 1, 2, 3)),
    FOREIGN KEY (franchise) REFERENCES franchise(franchise_id) ON DELETE SET NULL
);


-- Games --------------------------------------------------

CREATE TABLE IF NOT EXISTS game (
    game_id INTEGER PRIMARY KEY, 
    title_jap TEXT NOT NULL, 
    title_romanji TEXT NOT NULL, 
    title_eng TEXT DEFAULT "No english title",
    summary TEXT NOT NULL,
    franchise INTEGER,
    game_db_link VARCHAR(500) NOT NULL,
    publication_date DATE NOT NULL,
    FOREIGN KEY (franchise) REFERENCES franchise(franchise_id) ON DELETE SET NULL 
);


-- Creators ----------------------------------------------------------

CREATE TABLE IF NOT EXISTS author (
    author_id INTEGER PRIMARY KEY, 
    name_jap VARCHAR(200), 
    name_romanji VARCHAR(200)
);

CREATE TABLE IF NOT EXISTS illustrator (
    illustrator_id INTEGER PRIMARY KEY, 
    name_jap VARCHAR(200), 
    name_romanji VARCHAR(200)
);


CREATE TABLE IF NOT EXISTS studio (
    studio_id INTEGER PRIMARY KEY, 
    name_jap VARCHAR(200), 
    name_romanji VARCHAR(200)
);

CREATE TABLE IF NOT EXISTS developer (
    developer_id INTEGER PRIMARY KEY, 
    name_jap VARCHAR(200), 
    name_romanji VARCHAR(200)
);

CREATE TABLE IF NOT EXISTS anime_studio (
    studio_id INTEGER NOT NULL,
    anime_id INTEGER NOT NULL,
    PRIMARY KEY (anime_id, studio_id),
    FOREIGN KEY (studio_id) REFERENCES studio(studio_id) ON DELETE CASCADE,
    FOREIGN KEY (anime_id) REFERENCES anime(anime_id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS game_developer (
    developer_id INTEGER NOT NULL,
    game_id INTEGER NOT NULL,
    PRIMARY KEY (game_id, developer_id),
    FOREIGN KEY (developer_id) REFERENCES developer(developer_id) ON DELETE CASCADE,
    FOREIGN KEY (game_id) REFERENCES game(game_id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS manga_author (
    author_id INTEGER NOT NULL,
    manga_id INTEGER NOT NULL,
    PRIMARY KEY (manga_id, author_id),
    FOREIGN KEY (author_id) REFERENCES author(author_id) ON DELETE CASCADE,
    FOREIGN KEY (manga_id) REFERENCES manga(manga_id) ON DELETE CASCADE
);


CREATE TABLE IF NOT EXISTS light_novel_author (
    author_id INTEGER NOT NULL,
    light_novel_id INTEGER NOT NULL,
    PRIMARY KEY (light_novel_id, author_id),
    FOREIGN KEY (author_id) REFERENCES author(author_id) ON DELETE CASCADE,
    FOREIGN KEY (light_novel_id) REFERENCES light_novel(light_novel_id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS visual_novel_developer (
    developer_id INTEGER NOT NULL,
    visual_novel_id INTEGER NOT NULL,
    PRIMARY KEY (visual_novel_id, developer_id),
    FOREIGN KEY (developer_id) REFERENCES developer(developer_id) ON DELETE CASCADE,
    FOREIGN KEY (visual_novel_id) REFERENCES visual_novel(visual_novel_id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS manga_illustrator (
    illustrator_id INTEGER NOT NULL,
    manga_id INTEGER NOT NULL,
    PRIMARY KEY (manga_id, illustrator_id),
    FOREIGN KEY (illustrator_id) REFERENCES illustrator(illustrator_id) ON DELETE CASCADE,
    FOREIGN KEY (manga_id) REFERENCES manga(manga_id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS light_novel_illustrator (
    illustrator_id INTEGER NOT NULL,
    light_novel_id INTEGER NOT NULL,
    PRIMARY KEY (light_novel_id, illustrator_id),
    FOREIGN KEY (illustrator_id) REFERENCES illustrator(illustrator_id) ON DELETE CASCADE,
    FOREIGN KEY (light_novel_id) REFERENCES light_novel(light_novel_id) ON DELETE CASCADE
);

-- List ----------------------------------------------------------

CREATE TABLE IF NOT EXISTS list (
    list_id INTEGER PRIMARY KEY, 
    list_name VARCHAR(50) NOT NULL,
    user_id INTEGER NOT NULL,
    FOREIGN KEY (user_id) REFERENCES user(user_id) ON DELETE CASCADE,
);


CREATE TABLE IF NOT EXISTS anime_list (
    list_id INTEGER NOT NULL,
    anime_id INTEGER NOT NULL,
    PRIMARY KEY (anime_id, list_id),
    FOREIGN KEY (list_id) REFERENCES list(list_id) ON DELETE CASCADE,
    FOREIGN KEY (anime_id) REFERENCES anime(anime_id) ON DELETE CASCADE,
);

CREATE TABLE IF NOT EXISTS manga_list (
    list_id INTEGER NOT NULL,
    manga_id INTEGER NOT NULL,
    PRIMARY KEY (manga_id, list_id),
    FOREIGN KEY (list_id) REFERENCES list(list_id) ON DELETE CASCADE,
    FOREIGN KEY (manga_id) REFERENCES manga(manga_id) ON DELETE CASCADE,
);

CREATE TABLE IF NOT EXISTS visual_novel_list (
    list_id INTEGER NOT NULL,
    visual_novel_id INTEGER NOT NULL,
    PRIMARY KEY (visual_novel_id, list_id),
    FOREIGN KEY (list_id) REFERENCES list(list_id) ON DELETE CASCADE,
    FOREIGN KEY (visual_novel_id) REFERENCES visual_novel(visual_novel_id) ON DELETE CASCADE,
);

CREATE TABLE IF NOT EXISTS game_list (
    list_id INTEGER NOT NULL,
    game_id INTEGER NOT NULL,
    PRIMARY KEY (game_id, list_id),
    FOREIGN KEY (list_id) REFERENCES list(list_id) ON DELETE CASCADE,
    FOREIGN KEY (game_id) REFERENCES game(game_id) ON DELETE CASCADE,
);

CREATE TABLE IF NOT EXISTS light_novel_list (
    list_id INTEGER NOT NULL,
    light_novel_id INTEGER NOT NULL,
    PRIMARY KEY (light_novel_id, list_id),
    FOREIGN KEY (list_id) REFERENCES list(list_id) ON DELETE CASCADE,
    FOREIGN KEY (light_novel_id) REFERENCES light_novel(light_novel_id) ON DELETE CASCADE,
);

-- Demographics ----------------------------------------------------------

CREATE TABLE IF NOT EXISTS demography (
    demo_id INTEGER NOT NULL,
    demo_name VARCHAR(20) NOT NULL,
    PRIMARY KEY (demo_id, demo_name)
);


CREATE TABLE IF NOT EXISTS anime_demography (
    demo_id INTEGER NOT NULL,
    anime_id INTEGER NOT NULL,
    PRIMARY KEY (demo_id, anime_id),
    FOREIGN KEY (demo_id) REFERENCES demography(demo_id) ON DELETE CASCADE,
    FOREIGN KEY (anime_id) REFERENCES anime(anime_id) ON DELETE CASCADE
);


-- Genres ----------------------------------------------------------

CREATE TABLE IF NOT EXISTS genre (
    genre_id INTEGER PRIMARY KEY,
    genre_name VARCHAR(20) NOT NULL,
    CONSTRAINT uq_genre_name UNIQUE (genre_name)
);


-- Franchise ----------------------------------------------------------

CREATE TABLE IF NOT EXISTS franchise (
    franchise_id INTEGER PRIMARY KEY,
    franchise_name VARCHAR(150) NOT NULL,
    parts INTEGER DEFAULT 1
);

-- Anime Season ----------------------------------------------------------

CREATE TABLE IF NOT EXSITS season (
    season_id INTEGER PRIMARY KEY,
    season VARCHAR(100) NOT NULL,
    CONSTRAINT uq_season UNIQUE (season);
);

CREATE TABLE IF NOT EXISTS anime_season ( 
    season_id INTEGER NOT NULL,
    anime_id INTEGER NOT NULL,
    PRIMARY KEY (anime_id, season_id), 
    FOREIGN KEY (anime_id) REFERENCES anime(anime_id) ON DELETE CASCADE,
);

-- Bridge Tables For Genres ----------------------------------------------------------

CREATE TABLE IF NOT EXISTS anime_genre (
    anime_id INTEGER NOT NULL, 
    genre_id INTEGER NOT NULL,
    PRIMARY KEY (anime_id, genre_id),
    FOREIGN KEY (anime_id) REFERENCES anime(anime_id) ON DELETE CASCADE,
    FOREIGN KEY (genre_id) REFERENCES genre(genre_id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS visual_novel_genre (
    visual_novel_id INTEGER NOT NULL, 
    genre_id INTEGER NOT NULL,
    PRIMARY KEY (visual_novel_id, genre_id),
    FOREIGN KEY (visual_novel_id) REFERENCES visual_novel(visual_novel_id) ON DELETE CASCADE,
    FOREIGN KEY (genre_id) REFERENCES genre(genre_id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS light_novel_genre (
    light_novel_id INTEGER NOT NULL, 
    genre_id INTEGER NOT NULL,
    PRIMARY KEY (light_novel_id, genre_id),
    FOREIGN KEY (light_novel_id) REFERENCES light_novel(light_novel_id) ON DELETE CASCADE,
    FOREIGN KEY (genre_id) REFERENCES genre(genre_id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS manga_genre (
    manga_id INTEGER NOT NULL, 
    genre_id INTEGER NOT NULL,
    PRIMARY KEY (manga_id, genre_id),
    FOREIGN KEY (manga_id) REFERENCES manga(manga_id) ON DELETE CASCADE,
    FOREIGN KEY (genre_id) REFERENCES genre(genre_id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS game_genre (
    game_id INTEGER NOT NULL, 
    genre_id INTEGER NOT NULL,
    PRIMARY KEY (game_id, genre_id),
    FOREIGN KEY (game_id) REFERENCES game(game_id) ON DELETE CASCADE,
    FOREIGN KEY (genre_id) REFERENCES genre(genre_id) ON DELETE CASCADE
);