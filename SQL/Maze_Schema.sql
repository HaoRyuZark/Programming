CREATE TABLE IF NOT EXISTS maps (
    id INTEGER,
    name VARCHAR(50) NOT NULL,
    wid INTEGER NOT NULL,
    len INTEGER NOT NULL,
    PRIMARY KEY(id),
    UNIQUE (name),
    CONSTRAINT valid_area CHECK (wid * len <= 100000),
    CONSTRAINT valid_dimensions CHECK (wid > 0 AND len > 0)
);

CREATE TABLE IF NOT EXISTS locations (
    map_id INTEGER NOT NULL,
    name CHAR(1) NOT NULL,
    x_coord INTEGER NOT NULL,
    y_coord INTEGER NOT NULL,
    PRIMARY KEY (map_id, name),
    FOREIGN KEY (map_id) REFERENCES maps(id) ON DELETE CASCADE,
    CONSTRAINT valid_name CHECK (name BETWEEN 'A' AND 'Z'),
    CONSTRAINT unique_coordinates UNIQUE (map_id, x_coord, y_coord),
    CONSTRAINT valid_coordinates CHECK (x_coord >= 0 AND y_coord >= 0)
);

CREATE TABLE IF NOT EXISTS obstacles (
    id INTEGER,
    map_id INTEGER NOT NULL,
    x_coord INTEGER NOT NULL,
    y_coord INTEGER NOT NULL,
    PRIMARY KEY (id),
    FOREIGN KEY (map_id) REFERENCES maps(id) ON DELETE CASCADE,
    CONSTRAINT unique_coordinates UNIQUE (map_id, x_coord, y_coord),
    CONSTRAINT valid_coordinates CHECK (x_coord >= 0 AND y_coord >= 0)
);

CREATE TABLE IF NOT EXISTS paths (
    id INTEGER,
    map_id INTEGER NOT NULL,
    start_loc CHAR(1) NOT NULL,
    end_loc CHAR(1) NOT NULL,
    path_length INTEGER NOT NULL,
    PRIMARY KEY (id),
    FOREIGN KEY (map_id) REFERENCES maps(id) ON DELETE CASCADE,
    FOREIGN KEY (map_id, start_loc) REFERENCES locations(map_id, name) ON DELETE CASCADE,
    FOREIGN KEY (map_id, end_loc) REFERENCES locations(map_id, name) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS path_coordinates (
    id INTEGER,
    path_id INTEGER NOT NULL,
    x_coord INTEGER NOT NULL,
    y_coord INTEGER NOT NULL,
    PRIMARY KEY (id),
    FOREIGN KEY (path_id) REFERENCES paths(id) ON DELETE CASCADE,
    CONSTRAINT valid_coordinates CHECK (x_coord >= 0 AND y_coord >= 0)
);

CREATE TRIGGER IF NOT EXISTS check_obstacle_bounds
    BEFORE INSERT ON obstacles
        FOR EACH ROW
        WHEN (NEW.x_coord >= (SELECT len FROM maps WHERE id = NEW.map_id) OR
          NEW.y_coord >= (SELECT wid FROM maps WHERE id = NEW.map_id))
        BEGIN
        SELECT RAISE(ABORT, 'Obstacle out of bounds');
END;

CREATE TRIGGER IF NOT EXISTS check_location_bounds
    BEFORE INSERT ON locations
        FOR EACH ROW
        WHEN (NEW.x_coord >= (SELECT len FROM maps WHERE id = NEW.map_id) OR
              NEW.y_coord >= (SELECT wid FROM maps WHERE id = NEW.map_id))
        BEGIN
        SELECT RAISE(ABORT, 'Location coordinates out of map bounds');
END;

CREATE TRIGGER IF NOT EXISTS check_path_coordinate_bounds
    BEFORE INSERT ON path_coordinates
    FOR EACH ROW
        WHEN (NEW.x_coord >= (SELECT len FROM maps WHERE id = (SELECT map_id FROM paths WHERE id = NEW.path_id)) OR
              NEW.y_coord >= (SELECT wid FROM maps WHERE id = (SELECT map_id FROM paths WHERE id = NEW.path_id)))
        BEGIN
        SELECT RAISE(ABORT, 'Path coordinate out of map bounds');
END;

CREATE TRIGGER IF NOT EXISTS check_location_not_obstacle
    BEFORE INSERT ON locations
    FOR EACH ROW
        WHEN EXISTS (
            SELECT 1 FROM obstacles
            WHERE obstacles.map_id = NEW.map_id
            AND obstacles.x_coord = NEW.x_coord
            AND obstacles.y_coord = NEW.y_coord
        )
    BEGIN
        SELECT RAISE(ABORT, 'Location coordinates cannot be the same as an obstacle');
END;

CREATE TRIGGER IF NOT EXISTS check_obstacle_not_location
    BEFORE INSERT ON obstacles
    FOR EACH ROW
        WHEN EXISTS (
            SELECT 1 FROM locations
            WHERE locations.map_id = NEW.map_id
            AND locations.x_coord = NEW.x_coord
            AND locations.y_coord = NEW.y_coord
        )
    BEGIN
        SELECT RAISE(ABORT, 'Obstacle coordinates cannot be the same as a location');
END;
