import QtQuick 2.0

Canvas {
   property variant color: "white"
   property Border border: Border{}
   property variant gradient;
   function createEllipse(ctx, aX, aY, aWidth, aHeight){
   var hB = (aWidth / 2) * .5522848,
   vB = (aHeight / 2) * .5522848,
   eX = aX + aWidth,
   eY = aY + aHeight,
   mX = aX + aWidth / 2,
   mY = aY + aHeight / 2;
   ctx.beginPath();
   ctx.moveTo(aX, mY);
   ctx.bezierCurveTo(aX, mY - vB, mX - hB, aY, mX, aY);
   ctx.bezierCurveTo(mX + hB, aY, eX, mY - vB, eX, mY);
   ctx.bezierCurveTo(eX, mY + vB, mX + hB, eY, mX, eY);
   ctx.bezierCurveTo(mX - hB, eY, aX, mY + vB, aX, mY);
   ctx.closePath();
   }
   onPaint: {
   var ctx = getContext();
   ctx.save();
   ctx.strokeStyle = border.color;
   ctx.fillStyle = color;
   ctx.lineWidth = 1
   createEllipse(ctx, 0, 0, width, height);
   var radgrad = ctx.createRadialGradient(45,45,10,52,50,30);
   if (gradient != undefined ){
   for (var i= 0 ; i< gradient.stops.length; ++i)
   radgrad.addColorStop(gradient.stops[i].position, gradient.stops[i].color);
   ctx.fillStyle = radgrad;
   }
   ctx.fill();
   ctx.stroke();
   ctx.restore();
   }
}

