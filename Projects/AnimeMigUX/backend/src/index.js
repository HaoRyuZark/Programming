import { express } from "express";
import { process } from "process";

import * as animeRouter from "./routers/animes.js"
import * as mangasRouter from "./routers/mangas.js"
import * as visualNovelsRouter from "./routers/visualNovels.js"
import * as lightNovelsRouter from "./routers/lightNovels.js"

const PORT = process.env.PORT || 8080;


const app = express(); 


app.use("/api/animes/", animeRouter);
app.use("/api/mangas/", mangasRouter);
app.use("/api/visual_novels/", visualNovelsRouter);
app.use("/api/light_novels/", lightNovelsRouter);

app.listen(PORT, () => console.log(`Running on port ${PORT}`));


