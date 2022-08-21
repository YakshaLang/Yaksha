package com.intellij.model.psi.impl;

import com.google.common.collect.ImmutableList;
import com.intellij.model.Pointer;
import com.intellij.navigation.NavigatableSymbol;
import com.intellij.navigation.NavigationTarget;
import com.intellij.navigation.TargetPresentation;
import com.intellij.openapi.editor.markup.TextAttributes;
import com.intellij.openapi.project.Project;
import com.intellij.pom.Navigatable;
import com.intellij.psi.PsiElement;
import com.intellij.psi.SmartPointerManager;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import javax.swing.*;
import java.awt.*;
import java.util.Collection;

final class YkPsi2Symbol implements NavigatableSymbol {

  private final @NotNull PsiElement myElement;
  private final @NotNull Pointer<YkPsi2Symbol> myPointer;

  private final @NotNull NavigationTarget target;

  YkPsi2Symbol(@NotNull PsiElement element) {
    this(element, new MyPointer(element));
  }

  YkPsi2Symbol(@NotNull PsiElement element, @NotNull Pointer<YkPsi2Symbol> pointer) {
    myElement = element;
    myPointer = pointer;
    target = new NavigationTarget() {
      @Override
      public boolean isValid() {
        return true;
      }

      @Override
      public @NotNull Navigatable getNavigatable() {
        return (Navigatable) element;
      }

      @Override
      public @NotNull TargetPresentation getTargetPresentation() {
        return new TargetPresentation() {
          @Nullable
          @Override
          public Color getBackgroundColor() {
            return null;
          }

          @Nullable
          @Override
          public Icon getIcon() {
            return null;
          }

          @NotNull
          @Override
          public String getPresentableText() {
            return "null";
          }

          @Nullable
          @Override
          public TextAttributes getPresentableTextAttributes() {
            return null;
          }

          @Nullable
          @Override
          public String getContainerText() {
            return null;
          }

          @Nullable
          @Override
          public TextAttributes getContainerTextAttributes() {
            return null;
          }

          @Nullable
          @Override
          public String getLocationText() {
            return null;
          }

          @Nullable
          @Override
          public Icon getLocationIcon() {
            return null;
          }
        };
      }
    };
  }

  @NotNull
  PsiElement getElement() {
    return myElement;
  }

  @NotNull
  @Override
  public Pointer<YkPsi2Symbol> createPointer() {
    return myPointer;
  }

  @Override
  public @NotNull Collection<? extends NavigationTarget> getNavigationTargets(@NotNull Project project) {
    return ImmutableList.of(target);
  }

  private static final class MyPointer implements Pointer<YkPsi2Symbol> {

    private final @NotNull Pointer<? extends PsiElement> myPointer;

    private MyPointer(@NotNull PsiElement element) {
      myPointer = SmartPointerManager.createPointer(element);
    }

    @Nullable
    @Override
    public YkPsi2Symbol dereference() {
      PsiElement element = myPointer.dereference();
      if (element == null) {
        return null;
      }
      else {
        return new YkPsi2Symbol(element, this);
      }
    }

    @Override
    public boolean equals(Object o) {
      if (this == o) return true;
      if (o == null || getClass() != o.getClass()) return false;

      MyPointer pointer = (MyPointer)o;

      if (!myPointer.equals(pointer.myPointer)) return false;

      return true;
    }

    @Override
    public int hashCode() {
      return myPointer.hashCode();
    }
  }
}