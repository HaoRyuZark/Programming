# MigUX Anime Page

This page should work as an access point for my personal collection of anime, manga, visual novels and 
light novels, games, and eventually other kind of media if so wished. 

--- 

## Functional Features

List of features the page should have: 

- It should permit the search by title of the media. 
- The search should allow for filters. 
- The database should be up-to-date with a monthly scheduled update script and manually.
- It should be possible for anime to be watched from inside the page 
- It should be possible to read manga inside the page following the style of TMO.
- It should be possible to download the content from the page. 

> Note: Temporally the fetching of the data wil be performed using different API's which then will be centralized under a local database.

--- 

## Non-functional Features

- Each of the pages should have an specific aesthetic like: frutiger aero for the search, 90s for the player, etc.

- The page should be accessible via VPN. 

- A web scrapper or some kind of automatic workflow should be implemented to allow for the updating of the content without dependence on 
MyAnimeList or external sources. (Data Pipeline). 

--- 

--- 


## Backend 

--- 

## Frontend 

--- 

## Database 

The database layer of this application should be simple yet functional. We habe the following entites:

- User: has **name**, **email** and **password**.

- Author: **name**

- Anime/Manga/Novel: **title**, **genre**, **author**,


Links: 

- [Jikan API](https://jikan.moe/): this our main source of data which we will use to migrate the data to our own database.
- [MyAnimeList](https://myanimelist.net/): this is the main source of data for the Jikan API.
- [MangaDex](https://mangadex.org/): this a specialized source of data for manga and light novels which we will use to migrate the data to our own database. 
- [AniList](https://anilist.co/): this is a specialized source of data for anime and manga which we will use to migrate the data to our own database.
- [Anime News Network](https://www.animenewsnetwork.com/): we will use this for news and announcements related to anime, manga, and light novels.
- [MobyGames](https://www.mobygames.com/): we will use this for news and announcements related to video games.

I will take a look at the different API specifications to decide the schema to be used. Other sources will be used to fetch news and announcements we will use to update the database.

--- 

## System Architecture 

--- 





