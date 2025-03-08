## Contributing

Contributions are both encouraged and greatly appreciated.

To contribute content, fork this repo and make a pull request to the master branch including your changes.

- On GitHub, fork the tdeck-keyboard repo
- Clone your newly created repo. (Note: replace your-username with your GitHub username)

via ssh:

```
git clone git@github.com:your-username/tdeck-keyboard
```

via https:

```
git clone https://github.com/your-username/tdeck-keyboard
```

- Navigate to the repo and create a new topic branch

```
cd tdeck-keyboard
git checkout -b foobar
```

- After making modifications, commit and push your changes to your topic branch
- Open a PR against the tdeck-keyboard main branch

## Run the documentation server locally

This documentation can be built and run locally.

- The build process for mkdocs utilizes Python
- It is recommended to install python pip dependencies inside of a Virtual Environment [(venv)](https://squidfunk.github.io/mkdocs-material/guides/creating-a-reproduction/#environment)

Note: You may need to first install `python3-venv` or the equivalent for your distribution

- Navigate to your `tdeck-keyboard` repo
- Create the python virtual environment

```bash
python3 -m venv .venv
source .venv/bin/activate
```

- Install mkdocs dependencies to the venv

```bash
pip install -r requirements.txt
```

- Run the documentation server locally

```bash
mkdocs serve
```

- View your changes at [http://localhost:8000](http://localhost:8000)