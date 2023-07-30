package org.intellij.sdk.language;

import com.intellij.openapi.editor.colors.TextAttributesKey;
import com.intellij.openapi.fileTypes.SyntaxHighlighter;
import com.intellij.openapi.options.colors.AttributesDescriptor;
import com.intellij.openapi.options.colors.ColorDescriptor;
import com.intellij.openapi.options.colors.ColorSettingsPage;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import javax.swing.*;
import java.util.Map;

public class YakshaColorSettingsPage implements ColorSettingsPage {

    private static final AttributesDescriptor[] DESCRIPTORS = new AttributesDescriptor[]{
            new AttributesDescriptor("Operator", YakshaSyntaxHighlighter.SIGN),
            new AttributesDescriptor("Keyword", YakshaSyntaxHighlighter.KEYWORD),
            new AttributesDescriptor("String", YakshaSyntaxHighlighter.STRING),
            new AttributesDescriptor("Number", YakshaSyntaxHighlighter.NUMBER),
            new AttributesDescriptor("Data type", YakshaSyntaxHighlighter.DATA_TYPE),
            new AttributesDescriptor("Bad value", YakshaSyntaxHighlighter.BAD_CHARACTER),
            new AttributesDescriptor("Comment", YakshaSyntaxHighlighter.COMMENT),
            new AttributesDescriptor("Param", YakshaSyntaxHighlighter.PARAM),
            new AttributesDescriptor("MacroCall", YakshaSyntaxHighlighter.META_PROGRAMMING),
    };

    @Nullable
    @Override
    public Icon getIcon() {
        return YakshaIcons.FILE;
    }

    @NotNull
    @Override
    public SyntaxHighlighter getHighlighter() {
        return new YakshaSyntaxHighlighter();
    }

    @NotNull
    @Override
    public String getDemoText() {
        return "macros!{\n" +
                "    (defun to_fb (n) (+ (if (== n 1) \"\" \" \") (cond\n" +
                "        ((== 0 (modulo n 15)) \"FizzBuzz\")\n" +
                "        ((== 0 (modulo n 3)) \"Fizz\")\n" +
                "        ((== 0 (modulo n 5)) \"Buzz\")\n" +
                "        (true (to_string n))\n" +
                "        )))\n" +
                "    (defun fizzbuzz () (list (yk_create_token YK_TOKEN_STRING (reduce + (map to_fb (range 1 101))))))\n" +
                "    (yk_register {dsl fizzbuzz fizzbuzz})\n" +
                "}\n\n" +
                "import raylib as rl\n" +
                "import raylib.utils\n" +
                "import libs.numbers as num\n" +
                "import libs.perlin\n" +
                "import libs.random\n" +
                "\n" +
                "\n" +
                "class State:\n" +
                "    # State object to store state of branch\n" +
                "    width: float\n" +
                "    height: float\n" +
                "    angle: float\n" +
                "    frame_count: u64\n" +
                "    blue: rl.Color\n" +
                "    green: rl.Color\n" +
                "    color3: rl.Color\n" +
                "\n\n" +
                "struct Hello:\n" +
                "    world: int\n" +
                "\n\n" +
                "def branch(x: float, y: float, length: float, angle: float, s: State) -> None:\n" +
                "    if length < 4.0f:\n" +
                "        leaf_width: float = random.random_betweenf(1.0f, 3.0f)\n" +
                "        leaf_height: float = random.random_betweenf(3.0f, 6.0f)\n" +
                "        lerped_green: rl.Color = utils.lerp_color(s.green, s.blue, utils.remap(x, 0.0f, s.width, 0.0f, 1.0f) * 2.0f)\n" +
                "        color: rl.Color = utils.lerp_color(lerped_green, s.color3, utils.remap(y, 0.0f, s.height, 0.0f, 1.0f) * 1.5f)\n" +
                "        rl.draw_ellipse(num.f2i(x), num.f2i(y), leaf_height, leaf_width, color)\n" +
                "        return\n" +
                "    wind: float = utils.sin_deg(perlin.noise1df(num.uu2f(s.frame_count) / 50.0f)) * 100.0f * utils.sin_deg(num.uu2f(s.frame_count) / 2.0f)\n" +
                "    next_y: float = y - length * utils.cos_deg(angle)\n" +
                "    next_x: float = x + length * utils.sin_deg(angle)\n" +
                "    thick: float = utils.remap(length, 0.0f, s.height / 4.0f, 2.0f, 6.0f)\n" +
                "    rl.draw_line_ex(rl.vector2(x, y),\n" +
                "                    rl.vector2(next_x, next_y),\n" +
                "                    thick,\n" +
                "                    rl.color(152, 50, 1, 255))\n" +
                "    r1: float = random.random_betweenf(0.3f, 0.9f)\n" +
                "    r2: float = random.random_betweenf(0.5f, 0.8f)\n" +
                "    branch(next_x, next_y, (length * r2), angle + s.angle + wind * 10.0f, s)\n" +
                "    branch(next_x, next_y, (length * r1), angle - s.angle + wind * 10.0f, s)\n" +
                "\n" +
                "\n" +
                "def update_draw_frame(s: State) -> None:\n" +
                "    rl.clear_background(rl.color(255, 255, 255, 255))\n" +
                "    branch(s.width / 2.0f, s.height, s.height / 4.0f, 0.0f, s)\n" +
                "\n" +
                "\n" +
                "def main() -> int:\n" +
                "    s: State = State()\n" +
                "    s.angle = random.random_betweenf(30.0f, 45.0f)\n" +
                "    s.width = 600.0f\n" +
                "    s.height = 600.0f\n" +
                "    s.frame_count = num.i2uu(0)\n" +
                "    s.blue = rl.color(0, 255, 214, 255)\n" +
                "    s.green = rl.color(0, 255, 0, 255)\n" +
                "    s.color3 = rl.color(255, 45, 156, 255)\n" +
                "    rl.init_window(num.f2i(s.width), num.f2i(s.height), \"Fractal Tree in the Wind\")\n" +
                "    rl.set_target_fps(120)\n" +
                "    seed: u64 = random.init_random()\n" +
                "    while not rl.window_should_close():\n" +
                "        rl.begin_drawing()\n" +
                "        update_draw_frame(s)\n" +
                "        rl.draw_fps(0, 0)\n" +
                "        rl.end_drawing()\n" +
                "        s.frame_count = s.frame_count + num.i2uu(1)\n" +
                "        random.set_seed(seed)\n" +
                "    rl.close_window()\n" +
                "    del s\n" +
                "    return 0";
    }

    @Nullable
    @Override
    public Map<String, TextAttributesKey> getAdditionalHighlightingTagToDescriptorMap() {
        return null;
    }

    @Override
    public AttributesDescriptor @NotNull [] getAttributeDescriptors() {
        return DESCRIPTORS;
    }

    @Override
    public ColorDescriptor @NotNull [] getColorDescriptors() {
        return ColorDescriptor.EMPTY_ARRAY;
    }

    @NotNull
    @Override
    public String getDisplayName() {
        return "Yaksha";
    }

}