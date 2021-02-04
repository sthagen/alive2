; Introduction of nonnull isn't immediate UB
; ERROR: Target is more poisonous than source

define i8* @src(i8* %p) {
  ret i8* %p
}

define i8* @tgt(i8* nonnull %p) {
  ret i8* %p
}
