import datetime
import os

FILE_PATH = os.path.dirname(os.path.realpath(__file__))
LIBS_PATH = os.path.join(FILE_PATH, '../libs')

LIBS_FILE = os.path.join(LIBS_PATH, 'libs.yaka')
RELEASE_FILE = os.path.join(FILE_PATH, 'release.ini')

def main():
    current_date = datetime.datetime.now().strftime('%Y%m%d')
    # update return "version" in libs.yaka to alpha-yyyymmdd
    with open(LIBS_FILE, 'r', encoding="utf-8") as f:
        lines = f.read().splitlines(keepends=False)
        for i, line in enumerate(lines):
            if 'return "' in line:
                lines[i] = '    return "nightly-' + current_date + '"'
                break
    with open(LIBS_FILE, 'w', encoding="utf-8") as f:
        f.write('\n'.join(lines) + '\n')
    # update version="version" in release.ini to alpha-yyyymmdd
    with open(RELEASE_FILE, 'r', encoding="utf-8") as f:
        lines = f.read().splitlines(keepends=False)
        for i, line in enumerate(lines):
            if 'version=' in line:
                lines[i] = 'version=nightly-' + current_date
                break
    with open(RELEASE_FILE, 'w', encoding="utf-8") as f:
        f.write('\n'.join(lines) + '\n')
    # call release.py
    os.system('python ' + os.path.join(FILE_PATH, 'release.py'))


if __name__ == '__main__':
    main()
