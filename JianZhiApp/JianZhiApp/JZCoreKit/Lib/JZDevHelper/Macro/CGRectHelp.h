//
//  CGRectHelp.h
//  JZAppDemo
//
//  Created by Jie  on 2017/7/24.
//  Copyright © 2017年 Jie . All rights reserved.
//  Copy from QMUI..

#define ScreenScale ([[UIScreen mainScreen] scale])

#pragma mark - 适配
static inline NSInteger UIAdapter (float x){
    CGFloat scale = UIScreen.mainScreen.bounds.size.width / 375.0f; // 根据视觉UI稿
    return (NSInteger)x / scale;
}

static inline CGRect UIRectAdapter(x, y, width, height){
    return CGRectMake(UIAdapter(x), UIAdapter(y), UIAdapter(width), UIAdapter(height));
}

#pragma mark - CGFloat

/**
 *  基于指定的倍数，对传进来的 floatValue 进行像素取整。若指定倍数为0，则表示以当前设备的屏幕倍数为准。
 *
 *  例如传进来 “2.1”，在 2x 倍数下会返回 2.5（0.5pt 对应 1px），在 3x 倍数下会返回 2.333（0.333pt 对应 1px）。
 */
CG_INLINE CGFloat
flatSpecificScale(CGFloat floatValue, CGFloat scale) {
    scale = scale == 0 ? ScreenScale : scale;
    CGFloat flattedValue = ceil(floatValue * scale) / scale;
    return flattedValue;
}

/**
 *  基于当前设备的屏幕倍数，对传进来的 floatValue 进行像素取整。
 *
 *  注意如果在 Core Graphic 绘图里使用时，要注意当前画布的倍数是否和设备屏幕倍数一致，若不一致，不可使用 flat() 函数，而应该用 flatSpecificScale
 */
CG_INLINE CGFloat
flat(CGFloat floatValue) {
    return flatSpecificScale(floatValue, 0);
}

/**
 *  类似flat()，只不过 flat 是向上取整，而 floorInPixel 是向下取整
 */
CG_INLINE CGFloat
floorInPixel(CGFloat floatValue) {
    CGFloat resultValue = floor(floatValue * ScreenScale) / ScreenScale;
    return resultValue;
}

CG_INLINE BOOL
between(CGFloat minimumValue, CGFloat value, CGFloat maximumValue) {
    return minimumValue < value && value < maximumValue;
}

CG_INLINE BOOL
betweenOrEqual(CGFloat minimumValue, CGFloat value, CGFloat maximumValue) {
    return minimumValue <= value && value <= maximumValue;
}

/**
 *  调整给定的某个 CGFloat 值的小数点精度，超过精度的部分按四舍五入处理。
 *
 *  例如 CGFloatToFixed(0.3333, 2) 会返回 0.33，而 CGFloatToFixed(0.6666, 2) 会返回 0.67
 *
 *  @warning 参数类型为 CGFloat，也即意味着不管传进来的是 float 还是 double 最终都会被强制转换成 CGFloat 再做计算
 */
CG_INLINE CGFloat
CGFloatToFixed(CGFloat value, NSUInteger precision) {
    NSString *formatString = [NSString stringWithFormat:@"%%.%@f", @(precision)];
    NSString *toString = [NSString stringWithFormat:formatString, value];
#if defined(__LP64__) && __LP64__
    CGFloat result = [toString doubleValue];
#else
    CGFloat result = [toString floatValue];
#endif
    return result;
}

/// 用于居中运算
CG_INLINE CGFloat
CGFloatGetCenter(CGFloat parent, CGFloat child) {
    return flat((parent - child) / 2.0);
}

#pragma mark - CGPoint

/// 两个point相加
CG_INLINE CGPoint
CGPointUnion(CGPoint point1, CGPoint point2) {
    return CGPointMake(flat(point1.x + point2.x), flat(point1.y + point2.y));
}

/// 获取rect的center，包括rect本身的x/y偏移
CG_INLINE CGPoint
CGPointGetCenterWithRect(CGRect rect) {
    return CGPointMake(flat(CGRectGetMidX(rect)), flat(CGRectGetMidY(rect)));
}

CG_INLINE CGPoint
CGPointGetCenterWithSize(CGSize size) {
    return CGPointMake(flat(size.width / 2.0), flat(size.height / 2.0));
}

CG_INLINE CGPoint
CGPointToFixed(CGPoint point, NSUInteger precision) {
    CGPoint result = CGPointMake(CGFloatToFixed(point.x, precision), CGFloatToFixed(point.y, precision));
    return result;
}

#pragma mark - UIEdgeInsets

/// 获取UIEdgeInsets在水平方向上的值
CG_INLINE CGFloat
UIEdgeInsetsGetHorizontalValue(UIEdgeInsets insets) {
    return insets.left + insets.right;
}

/// 获取UIEdgeInsets在垂直方向上的值
CG_INLINE CGFloat
UIEdgeInsetsGetVerticalValue(UIEdgeInsets insets) {
    return insets.top + insets.bottom;
}

/// 将两个UIEdgeInsets合并为一个
CG_INLINE UIEdgeInsets
UIEdgeInsetsConcat(UIEdgeInsets insets1, UIEdgeInsets insets2) {
    insets1.top += insets2.top;
    insets1.left += insets2.left;
    insets1.bottom += insets2.bottom;
    insets1.right += insets2.right;
    return insets1;
}

CG_INLINE UIEdgeInsets
UIEdgeInsetsSetTop(UIEdgeInsets insets, CGFloat top) {
    insets.top = flat(top);
    return insets;
}

CG_INLINE UIEdgeInsets
UIEdgeInsetsSetLeft(UIEdgeInsets insets, CGFloat left) {
    insets.left = flat(left);
    return insets;
}

CG_INLINE UIEdgeInsets
UIEdgeInsetsSetBottom(UIEdgeInsets insets, CGFloat bottom) {
    insets.bottom = flat(bottom);
    return insets;
}

CG_INLINE UIEdgeInsets
UIEdgeInsetsSetRight(UIEdgeInsets insets, CGFloat right) {
    insets.right = flat(right);
    return insets;
}

CG_INLINE UIEdgeInsets
UIEdgeInsetsToFixed(UIEdgeInsets insets, NSUInteger precision) {
    UIEdgeInsets result = UIEdgeInsetsMake(CGFloatToFixed(insets.top, precision), CGFloatToFixed(insets.left, precision), CGFloatToFixed(insets.bottom, precision), CGFloatToFixed(insets.right, precision));
    return result;
}

#pragma mark - CGSize

/// 判断一个size是否为空（宽或高为0）
CG_INLINE BOOL
CGSizeIsEmpty(CGSize size) {
    return size.width <= 0 || size.height <= 0;
}

/// 将一个CGSize像素对齐
CG_INLINE CGSize
CGSizeFlatted(CGSize size) {
    return CGSizeMake(flat(size.width), flat(size.height));
}

/// 将一个 CGSize 以 pt 为单位向上取整
CG_INLINE CGSize
CGSizeCeil(CGSize size) {
    return CGSizeMake(ceil(size.width), ceil(size.height));
}

/// 将一个 CGSize 以 pt 为单位向下取整
CG_INLINE CGSize
CGSizeFloor(CGSize size) {
    return CGSizeMake(floor(size.width), floor(size.height));
}

CG_INLINE CGSize
CGSizeToFixed(CGSize size, NSUInteger precision) {
    CGSize result = CGSizeMake(CGFloatToFixed(size.width, precision), CGFloatToFixed(size.height, precision));
    return result;
}

#pragma mark - CGRect

/// 判断一个 CGRect 是否存在NaN
CG_INLINE BOOL
CGRectIsNaN(CGRect rect) {
    return isnan(rect.origin.x) || isnan(rect.origin.y) || isnan(rect.size.width) || isnan(rect.size.height);
}

/// 判断一个 CGRect 是否合法（例如不带无穷大的值、不带非法数字、不为空）
CG_INLINE BOOL
CGRectIsValidated(CGRect rect) {
    return !CGRectIsNull(rect) && !CGRectIsEmpty(rect) && !CGRectIsInfinite(rect) && !CGRectIsNaN(rect);
}

/// 创建一个像素对齐的CGRect
CG_INLINE CGRect
CGRectFlatMake(CGFloat x, CGFloat y, CGFloat width, CGFloat height) {
    return CGRectMake(flat(x), flat(y), flat(width), flat(height));
}

/// 对CGRect的x/y、width/height都调用一次flat，以保证像素对齐
CG_INLINE CGRect
CGRectFlatted(CGRect rect) {
    return CGRectMake(flat(rect.origin.x), flat(rect.origin.y), flat(rect.size.width), flat(rect.size.height));
}

/// 为一个CGRect叠加scale计算
CG_INLINE CGRect
CGRectApplyScale(CGRect rect, CGFloat scale) {
    return CGRectFlatted(CGRectMake(CGRectGetMinX(rect) * scale, CGRectGetMinY(rect) * scale, CGRectGetWidth(rect) * scale, CGRectGetHeight(rect) * scale));
}

/// 计算view的水平居中，传入父view和子view的frame，返回子view在水平居中时的x值
CG_INLINE CGFloat
CGRectGetMinXHorizontallyCenterInParentRect(CGRect parentRect, CGRect childRect) {
    return flat((CGRectGetWidth(parentRect) - CGRectGetWidth(childRect)) / 2.0);
}

/// 计算view的垂直居中，传入父view和子view的frame，返回子view在垂直居中时的y值
CG_INLINE CGFloat
CGRectGetMinYVerticallyCenterInParentRect(CGRect parentRect, CGRect childRect) {
    return flat((CGRectGetHeight(parentRect) - CGRectGetHeight(childRect)) / 2.0);
}

/// 返回值：同一个坐标系内，想要layoutingRect和已布局完成的referenceRect保持垂直居中时，layoutingRect的originY
CG_INLINE CGFloat
CGRectGetMinYVerticallyCenter(CGRect referenceRect, CGRect layoutingRect) {
    return CGRectGetMinY(referenceRect) + CGRectGetMinYVerticallyCenterInParentRect(referenceRect, layoutingRect);
}

/// 返回值：同一个坐标系内，想要layoutingRect和已布局完成的referenceRect保持水平居中时，layoutingRect的originX
CG_INLINE CGFloat
CGRectGetMinXHorizontallyCenter(CGRect referenceRect, CGRect layoutingRect) {
    return CGRectGetMinX(referenceRect) + CGRectGetMinXHorizontallyCenterInParentRect(referenceRect, layoutingRect);
}

/// 为给定的rect往内部缩小insets的大小
CG_INLINE CGRect
CGRectInsetEdges(CGRect rect, UIEdgeInsets insets) {
    rect.origin.x += insets.left;
    rect.origin.y += insets.top;
    rect.size.width -= UIEdgeInsetsGetHorizontalValue(insets);
    rect.size.height -= UIEdgeInsetsGetVerticalValue(insets);
    return rect;
}

/// 传入size，返回一个x/y为0的CGRect
CG_INLINE CGRect
CGRectMakeWithSize(CGSize size) {
    return CGRectMake(0, 0, size.width, size.height);
}

CG_INLINE CGRect
CGRectFloatTop(CGRect rect, CGFloat top) {
    rect.origin.y = top;
    return rect;
}

CG_INLINE CGRect
CGRectFloatBottom(CGRect rect, CGFloat bottom) {
    rect.origin.y = bottom - CGRectGetHeight(rect);
    return rect;
}

CG_INLINE CGRect
CGRectFloatRight(CGRect rect, CGFloat right) {
    rect.origin.x = right - CGRectGetWidth(rect);
    return rect;
}

CG_INLINE CGRect
CGRectFloatLeft(CGRect rect, CGFloat left) {
    rect.origin.x = left;
    return rect;
}

/// 保持rect的左边缘不变，改变其宽度，使右边缘靠在right上
CG_INLINE CGRect
CGRectLimitRight(CGRect rect, CGFloat rightLimit) {
    rect.size.width = rightLimit - rect.origin.x;
    return rect;
}

/// 保持rect右边缘不变，改变其宽度和origin.x，使其左边缘靠在left上。只适合那种右边缘不动的view
/// 先改变origin.x，让其靠在offset上
/// 再改变size.width，减少同样的宽度，以抵消改变origin.x带来的view移动，从而保证view的右边缘是不动的
CG_INLINE CGRect
CGRectLimitLeft(CGRect rect, CGFloat leftLimit) {
    CGFloat subOffset = leftLimit - rect.origin.x;
    rect.origin.x = leftLimit;
    rect.size.width = rect.size.width - subOffset;
    return rect;
}

/// 限制rect的宽度，超过最大宽度则截断，否则保持rect的宽度不变
CG_INLINE CGRect
CGRectLimitMaxWidth(CGRect rect, CGFloat maxWidth) {
    CGFloat width = CGRectGetWidth(rect);
    rect.size.width = width > maxWidth ? maxWidth : width;
    return rect;
}

CG_INLINE CGRect
CGRectSetX(CGRect rect, CGFloat x) {
    rect.origin.x = flat(x);
    return rect;
}

CG_INLINE CGRect
CGRectSetY(CGRect rect, CGFloat y) {
    rect.origin.y = flat(y);
    return rect;
}

CG_INLINE CGRect
CGRectSetXY(CGRect rect, CGFloat x, CGFloat y) {
    rect.origin.x = flat(x);
    rect.origin.y = flat(y);
    return rect;
}

CG_INLINE CGRect
CGRectSetWidth(CGRect rect, CGFloat width) {
    rect.size.width = flat(width);
    return rect;
}

CG_INLINE CGRect
CGRectSetHeight(CGRect rect, CGFloat height) {
    rect.size.height = flat(height);
    return rect;
}

CG_INLINE CGRect
CGRectSetSize(CGRect rect, CGSize size) {
    rect.size = CGSizeFlatted(size);
    return rect;
}

CG_INLINE CGRect
CGRectToFixed(CGRect rect, NSUInteger precision) {
    CGRect result = CGRectMake(CGFloatToFixed(CGRectGetMinX(rect), precision),
                               CGFloatToFixed(CGRectGetMinY(rect), precision),
                               CGFloatToFixed(CGRectGetWidth(rect), precision),
                               CGFloatToFixed(CGRectGetHeight(rect), precision));
    return result;
}

#pragma mark - Custom
/**
 *  返回一个根据6s屏幕z为基准，等宽高比的Rect
 */
CG_INLINE CGRect
CGRectByScale(CGFloat x, CGFloat y, CGFloat width, CGFloat height) {
    return CGRectMake(flat(x), flat(y), flat(width), flat(height));
}

/**
 *  返回屏幕宽度比
 */
//CG_INLINE CGFloat
//CGScreenWidthScale(CGFloat floatValue) {
//
//}
