# 🌀 curl Cheatsheet

`curl` is a command-line tool for transferring data with URLs. It supports HTTP, HTTPS, FTP, and more.

---

## 🔹 Basic Usage
```bash
curl https://example.com
````

* Fetch a web page and output to terminal.

```bash
curl -o file.html https://example.com
```

* Save response to a file (`file.html`).

```bash
curl -O https://example.com/file.zip
```

* Save with the same filename as remote (`file.zip`).

---

## 🔹 HTTP Methods

```bash
curl -X GET https://api.example.com/users
curl -X POST -d "name=John&age=30" https://api.example.com/users
curl -X PUT -d '{"name":"John"}' -H "Content-Type: application/json" https://api.example.com/users/1
curl -X DELETE https://api.example.com/users/1
```

---

## 🔹 Headers

```bash
curl -H "Accept: application/json" https://api.example.com/data
curl -H "Authorization: Bearer TOKEN" https://api.example.com/secure
```

* Multiple headers:

```bash
curl -H "Accept: application/json" -H "X-Custom: Value" https://example.com
```

---

## 🔹 Data

```bash
curl -d "key=value&another=value2" https://example.com/form
```

* Send form data (`application/x-www-form-urlencoded`).

```bash
curl -d '{"key":"value"}' -H "Content-Type: application/json" https://example.com/json
```

* Send JSON.

```bash
curl --data-binary @file.json https://example.com/upload
```

* Send raw file as request body.

---

## 🔹 Authentication

```bash
curl -u username:password https://example.com
```

* Basic auth.

```bash
curl -H "Authorization: Bearer TOKEN" https://example.com
```

* Token (Bearer/JWT).

---

## 🔹 Files & Uploads

```bash
curl -F "file=@path/to/file.txt" https://example.com/upload
```

* File upload (multipart form).

```bash
curl -F "file=@img.png" -F "name=MyImage" https://example.com/upload
```

* File + extra fields.

---

## 🔹 Redirects

```bash
curl -L https://short.url
```

* Follow redirects.

---

## 🔹 Output Options

```bash
curl -i https://example.com
```

* Include response headers.

```bash
curl -I https://example.com
```

* Fetch only headers.

```bash
curl -v https://example.com
```

* Verbose mode (debug).

```bash
curl -s https://example.com
```

* Silent mode (no progress bar).

```bash
curl -w "%{http_code}\n" -o /dev/null -s https://example.com
```

* Show only HTTP status code.

---

## 🔹 Cookies

```bash
curl -b "name=value" https://example.com
curl -c cookies.txt https://example.com
curl -b cookies.txt https://example.com
```

---

## 🔹 Downloading

```bash
curl -O https://example.com/file.zip
curl -O -J -L https://example.com/download
```

* `-J`: Use server-provided filename.
* `-L`: Follow redirects.

---

## 🔹 Rate Limiting / Timeout

```bash
curl --limit-rate 100K https://example.com/file.zip
curl --max-time 10 https://example.com
```

---

## 🔹 Proxy

```bash
curl -x http://proxy:8080 https://example.com
curl -x socks5://127.0.0.1:9050 https://example.com
```

---

## 🔹 Handy Shortcuts

* `-s`: Silent (no progress or errors)
* `-S`: Show errors even with `-s`
* `-k`: Ignore SSL cert errors
* `-v`: Verbose
* `-L`: Follow redirects
* `-o file`: Save as file
* `-O`: Save with remote filename

---

## 🔹 Examples

```bash
# Check if a site is up (status code only)
curl -s -o /dev/null -w "%{http_code}\n" https://example.com

# Download a file with resume support
curl -C - -O https://example.com/large.iso

# POST JSON with Bearer token
curl -X POST https://api.example.com/data \
     -H "Content-Type: application/json" \
     -H "Authorization: Bearer $TOKEN" \
     -d '{"id":123,"name":"Test"}'
```

---


```

