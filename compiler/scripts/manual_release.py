import datetime
import os
import subprocess

FILE_PATH = os.path.dirname(os.path.realpath(__file__))
LIBS_PATH = os.path.join(FILE_PATH, '../libs')

LIBS_FILE = os.path.join(LIBS_PATH, 'libs.yaka')
RELEASE_FILE = os.path.join(FILE_PATH, 'release.ini')

def execute(args: list):
    proc = subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE, encoding="utf-8",
                            universal_newlines=True, env=dict(os.environ))
    try:
        so, se = proc.communicate(timeout=6)
    except subprocess.TimeoutExpired:
        proc.kill()
        proc.communicate()
        return ""
    return so + se

def main():
    current_date = datetime.datetime.now().strftime('%Y%m%d')
    current_commit_hash = execute(['git', 'rev-parse', 'HEAD']).strip()[:7].lower()
    # A pre-release version -- vP20210101.abcdefg
    new_version = 'P' + current_date + '.' + current_commit_hash
    # update return "version" in libs.yaka
    with open(LIBS_FILE, 'r', encoding="utf-8") as f:
        lines = f.read().splitlines(keepends=False)
        for i, line in enumerate(lines):
            if 'return "' in line:
                lines[i] = '    return "' + new_version + '"'
                break
    with open(LIBS_FILE, 'w', encoding="utf-8") as f:
        f.write('\n'.join(lines) + '\n')
    # update version="version" in release.ini
    with open(RELEASE_FILE, 'r', encoding="utf-8") as f:
        lines = f.read().splitlines(keepends=False)
        for i, line in enumerate(lines):
            if 'version=' in line:
                lines[i] = 'version=' + new_version
                break
    with open(RELEASE_FILE, 'w', encoding="utf-8") as f:
        f.write('\n'.join(lines) + '\n')
    # call release.py
    os.system('python ' + os.path.join(FILE_PATH, 'release.py'))


if __name__ == '__main__':
    main()
